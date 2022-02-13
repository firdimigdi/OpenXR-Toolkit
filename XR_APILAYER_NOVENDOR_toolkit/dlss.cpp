// MIT License
//
// Copyright(c) 2022 Matthieu Bucchianeri
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this softwareand associated documentation files(the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright noticeand this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include "pch.h"

#include "factories.h"
#include "interfaces.h"
#include "layer.h"
#include "log.h"

#define CHECK_NVCMD(cmd) xr::detail::_CheckNVResult(cmd, #cmd, FILE_AND_LINE)

namespace xr::detail {

    [[noreturn]] inline void _ThrowNVResult(NVSDK_NGX_Result nvr,
                                            const char* originator = nullptr,
                                            const char* sourceLocation = nullptr) {
        xr::detail::_Throw(xr::detail::_Fmt("NVSDK_NGX_Result failure [%x]", nvr), originator, sourceLocation);
    }

    inline HRESULT _CheckNVResult(NVSDK_NGX_Result nvr,
                                  const char* originator = nullptr,
                                  const char* sourceLocation = nullptr) {
        if (NVSDK_NGX_FAILED(nvr)) {
            xr::detail::_ThrowNVResult(nvr, originator, sourceLocation);
        }

        return nvr;
    }

} // namespace xr::detail

namespace {

    using namespace toolkit;
    using namespace toolkit::config;
    using namespace toolkit::graphics;
    using namespace toolkit::log;

    class D3D11DLSS : public ISuperSampler {
      public:
        D3D11DLSS(std::shared_ptr<IConfigManager> configManager,
                  std::shared_ptr<IDevice> graphicsDevice,
                  uint32_t outputWidth,
                  uint32_t outputHeight,
                  NVSDK_NGX_Parameter* ngxParameters)
            : m_configManager(configManager), m_device(graphicsDevice), m_outputWidth(outputWidth),
              m_outputHeight(outputHeight), m_ngxParameters(ngxParameters) {
        }

        ~D3D11DLSS() override {
            if (m_dlssHandle) {
                NVSDK_NGX_D3D11_ReleaseFeature(m_dlssHandle);
            }
        }

        void update() override {
            // Updating the perf/quality mode is handled in upscale().
        }

        void upscale(std::shared_ptr<ITexture> input,
                     std::shared_ptr<ITexture> motionVectors,
                     std::shared_ptr<ITexture> depth,
                     bool isDepthInverted,
                     std::shared_ptr<ITexture> output,
                     int32_t slice = -1) override {
            if (m_device->getApi() == Api::D3D11) {
                // Lazily-created DLSS handle (we need to know if depth is inverted!).
                if (!m_dlssHandle || m_configManager->hasChanged(SettingDLSSMode)) {
                    if (m_dlssHandle) {
                        NVSDK_NGX_D3D11_ReleaseFeature(m_dlssHandle);
                    }

                    NVSDK_NGX_DLSS_Create_Params createParams;
                    ZeroMemory(&createParams, sizeof(NVSDK_NGX_DLSS_Create_Params));
                    createParams.InFeatureCreateFlags = NVSDK_NGX_DLSS_Feature_Flags_DoSharpening;
                    if (isDepthInverted) {
                        createParams.InFeatureCreateFlags |= NVSDK_NGX_DLSS_Feature_Flags_DepthInverted;
                    }
                    createParams.Feature.InTargetWidth = m_outputWidth;
                    createParams.Feature.InTargetHeight = m_outputHeight;
                    createParams.Feature.InWidth = input->getInfo().width;
                    createParams.Feature.InHeight = input->getInfo().height;
                    createParams.Feature.InPerfQualityValue =
                        m_configManager->getEnumValue<NVSDK_NGX_PerfQuality_Value>(SettingDLSSMode);
                    CHECK_NVCMD(NGX_D3D11_CREATE_DLSS_EXT(
                        m_device->getContext<D3D11>(), &m_dlssHandle, m_ngxParameters, &createParams));
                }

                auto context = m_device->getContext<D3D11>();
                std::shared_ptr<ITexture> realOutput = output;

                // Handle texture arrays.
                // This is really not optimal, but we have to copy everything into a single texture then the output
                // back. We only do that for the slices > 0 (because it seems to work for slice 0).
                if (slice > 0) {
                    if (!m_secondInput) {
                        auto info = input->getInfo();
                        info.arraySize = 1;
                        m_secondInput = m_device->createTexture(info, "DLSS Second Input TEX2D");
                    }
                    context->CopySubresourceRegion(
                        m_secondInput->getNative<D3D11>(), 0, 0, 0, 0, input->getNative<D3D11>(), slice, nullptr);
                    input = m_secondInput;

                    if (!m_secondMotionVectors) {
                        auto info = motionVectors->getInfo();
                        info.arraySize = 1;
                        m_secondMotionVectors = m_device->createTexture(info, "DLSS Second MV TEX2D");
                    }
                    context->CopySubresourceRegion(m_secondMotionVectors->getNative<D3D11>(),
                                                   0,
                                                   0,
                                                   0,
                                                   0,
                                                   motionVectors->getNative<D3D11>(),
                                                   slice,
                                                   nullptr);
                    motionVectors = m_secondMotionVectors;

                    if (!m_secondDepth) {
                        auto info = depth->getInfo();
                        info.arraySize = 1;

                        // Use Typeless formats.
                        switch (info.format) {
                        case DXGI_FORMAT_D32_FLOAT:
                            info.format = (int64_t)DXGI_FORMAT_R32_TYPELESS;
                            break;

                        case DXGI_FORMAT_D16_UNORM:
                            info.format = (int64_t)DXGI_FORMAT_R16_TYPELESS;
                            break;

                        case DXGI_FORMAT_D24_UNORM_S8_UINT:
                            info.format = (int64_t)DXGI_FORMAT_R24G8_TYPELESS;
                            break;

                        case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
                            info.format = (int64_t)DXGI_FORMAT_R32G8X24_TYPELESS;
                            break;
                        }

                        m_secondDepth = m_device->createTexture(info, "DLSS Second Depth TEX2D");
                    }
                    context->CopySubresourceRegion(
                        m_secondDepth->getNative<D3D11>(), 0, 0, 0, 0, depth->getNative<D3D11>(), slice, nullptr);
                    depth = m_secondDepth;

                    if (!m_secondOutput) {
                        auto info = output->getInfo();
                        info.arraySize = 1;
                        m_secondOutput = m_device->createTexture(info, "DLSS Second Output TEX2D");
                    }
                    output = m_secondOutput;
                }

                // Invoke DLSS.
                NVSDK_NGX_D3D11_DLSS_Eval_Params dlssParams;
                ZeroMemory(&dlssParams, sizeof(NVSDK_NGX_D3D11_DLSS_Eval_Params));
                dlssParams.Feature.pInColor = input->getNative<D3D11>();
                dlssParams.Feature.pInOutput = output->getNative<D3D11>();
                dlssParams.Feature.InSharpness = m_configManager->getValue(SettingSharpness) / 100.0f;
                dlssParams.pInDepth = depth->getNative<D3D11>();
                // TODO: Check if scale is 1?
                dlssParams.pInMotionVectors = motionVectors->getNative<D3D11>();
                // TODO: Adjust this?
                dlssParams.InJitterOffsetX = dlssParams.InJitterOffsetY = 0.0f;
                dlssParams.InRenderSubrectDimensions.Width = input->getInfo().width;
                dlssParams.InRenderSubrectDimensions.Height = input->getInfo().height;
                CHECK_NVCMD(NGX_D3D11_EVALUATE_DLSS_EXT(
                    m_device->getContext<D3D11>(), m_dlssHandle, m_ngxParameters, &dlssParams));

                if (output != realOutput) {
                    context->CopySubresourceRegion(
                        realOutput->getNative<D3D11>(), slice, 0, 0, 0, m_secondOutput->getNative<D3D11>(), 0, nullptr);
                }
            } else {
                throw std::runtime_error("Unsupported graphics runtime");
            }
        }

      private:
        const std::shared_ptr<IConfigManager> m_configManager;
        const std::shared_ptr<IDevice> m_device;
        const uint32_t m_outputWidth;
        const uint32_t m_outputHeight;
        NVSDK_NGX_Parameter* const m_ngxParameters;

        std::shared_ptr<ITexture> m_secondInput;
        std::shared_ptr<ITexture> m_secondMotionVectors;
        std::shared_ptr<ITexture> m_secondDepth;
        std::shared_ptr<ITexture> m_secondOutput;

        NVSDK_NGX_Handle* m_dlssHandle{nullptr};
    };

    class DLSSFactory : public ISuperSamplerFactory {
      public:
        DLSSFactory(std::shared_ptr<IConfigManager> configManager,
                    std::shared_ptr<IDevice> graphicsDevice,
                    uint32_t outputWidth,
                    uint32_t outputHeight)
            : m_configManager(configManager), m_device(graphicsDevice), m_outputWidth(outputWidth),
              m_outputHeight(outputHeight) {
            if (m_device->getApi() == Api::D3D11) {
                auto status = NVSDK_NGX_D3D11_Init_with_ProjectID("9bbe58f3-e8dd-4c7a-8a2c-1ab0eeb7a8b3",
                                                                  NVSDK_NGX_EngineType::NVSDK_NGX_ENGINE_TYPE_CUSTOM,
                                                                  "1.0.0",
                                                                  (localAppData / "logs").wstring().c_str(),
                                                                  m_device->getNative<D3D11>());
                if (NVSDK_NGX_FAILED(status)) {
                    Log("Failed to initialize NVSDK: %x\n", status);
                    throw FeatureNotSupported();
                }

                status = NVSDK_NGX_D3D11_GetCapabilityParameters(&m_ngxParameters);
                if (NVSDK_NGX_FAILED(status)) {
                    Log("Failed to query NVSDK: %x\n", status);
                    throw FeatureNotSupported();
                }
            } else if (m_device->getApi() == Api::D3D12) {
                auto status = NVSDK_NGX_D3D12_Init_with_ProjectID("9bbe58f3-e8dd-4c7a-8a2c-1ab0eeb7a8b3",
                                                                  NVSDK_NGX_EngineType::NVSDK_NGX_ENGINE_TYPE_CUSTOM,
                                                                  "1.0.0",
                                                                  (localAppData / "logs").wstring().c_str(),
                                                                  m_device->getNative<D3D12>());
                if (NVSDK_NGX_FAILED(status)) {
                    Log("Failed to initialize NVSDK: %x\n", status);
                    throw FeatureNotSupported();
                }

                status = NVSDK_NGX_D3D12_GetCapabilityParameters(&m_ngxParameters);
                if (NVSDK_NGX_FAILED(status)) {
                    Log("Failed to query NVSDK: %x\n", status);
                    throw FeatureNotSupported();
                }
            } else {
                throw std::runtime_error("Unsupported graphics runtime");
            }

            int dlssAvailable = 0;
            if (NVSDK_NGX_FAILED(m_ngxParameters->Get(NVSDK_NGX_Parameter_SuperSampling_Available, &dlssAvailable)) ||
                !dlssAvailable) {
                Log("DLSS is not supported for this adapter\n");
                throw FeatureNotSupported();
            }

            m_hasUltraSettings = true;
            {
                NVSDK_NGX_PerfQuality_Value perfQuality[] = {
                    NVSDK_NGX_PerfQuality_Value::NVSDK_NGX_PerfQuality_Value_MaxPerf,
                    NVSDK_NGX_PerfQuality_Value::NVSDK_NGX_PerfQuality_Value_Balanced,
                    NVSDK_NGX_PerfQuality_Value::NVSDK_NGX_PerfQuality_Value_MaxQuality,
                    NVSDK_NGX_PerfQuality_Value::NVSDK_NGX_PerfQuality_Value_UltraPerformance,
                    NVSDK_NGX_PerfQuality_Value::NVSDK_NGX_PerfQuality_Value_UltraQuality};
                std::string_view perfQualityString[ARRAYSIZE(perfQuality)] = {
                    "Maximum performance", "Balanced", "Maximum quality", "Ultra performance", "Ultra quality"};
                for (size_t i = 0; i < ARRAYSIZE(perfQuality); i++) {
                    unsigned int recommendedOptimalRenderWidth = 0, recommendedOptimalRenderHeight = 0,
                                 dynamicMaximumRenderSizeWidth, dynamicMaximumRenderSizeHeight,
                                 dynamicMinimumRenderSizeWidth, dynamicMinimumRenderSizeHeight;
                    float sharpness = 0.0f;
                    if (NVSDK_NGX_SUCCEED(NGX_DLSS_GET_OPTIMAL_SETTINGS(m_ngxParameters,
                                                                        m_outputWidth,
                                                                        m_outputHeight,
                                                                        perfQuality[i],
                                                                        &recommendedOptimalRenderWidth,
                                                                        &recommendedOptimalRenderHeight,
                                                                        &dynamicMaximumRenderSizeWidth,
                                                                        &dynamicMaximumRenderSizeHeight,
                                                                        &dynamicMinimumRenderSizeWidth,
                                                                        &dynamicMinimumRenderSizeHeight,
                                                                        &sharpness))) {
                        Log("DLSS profile for \"%s\": %ux%u, %.3f sharpening\n",
                            perfQualityString[i].data(),
                            recommendedOptimalRenderWidth,
                            recommendedOptimalRenderHeight,
                            sharpness);
                    } else {
                        m_hasUltraSettings = false;
                    }
                }
            }
        }

        ~DLSSFactory() override {
            if (m_device->getApi() == Api::D3D11) {
                if (m_ngxParameters) {
                    NVSDK_NGX_D3D11_DestroyParameters(m_ngxParameters);
                }
                NVSDK_NGX_D3D11_Shutdown();
            } else if (m_device->getApi() == Api::D3D12) {
                if (m_ngxParameters) {
                    NVSDK_NGX_D3D12_DestroyParameters(m_ngxParameters);
                }
                NVSDK_NGX_D3D12_Shutdown();
            }
        }

        std::shared_ptr<ISuperSampler> createSuperSampler() override {
            if (m_device->getApi() == Api::D3D11) {
                return std::make_shared<D3D11DLSS>(
                    m_configManager, m_device, m_outputWidth, m_outputHeight, m_ngxParameters);
            } else if (m_device->getApi() == Api::D3D12) {
                // TODO: DX12.
                assert(false);
                return nullptr;
            } else {
                throw std::runtime_error("Unsupported graphics runtime");
            }
        }

        bool hasUltraSettings() const override {
            return m_hasUltraSettings;
        }

      private:
        const std::shared_ptr<IConfigManager> m_configManager;
        const std::shared_ptr<IDevice> m_device;
        const uint32_t m_outputWidth;
        const uint32_t m_outputHeight;
        bool m_hasUltraSettings;

        NVSDK_NGX_Parameter* m_ngxParameters{nullptr};
    };

} // namespace

namespace toolkit::graphics {

    std::shared_ptr<ISuperSamplerFactory> CreateDLSSFactory(std::shared_ptr<IConfigManager> configManager,
                                                            std::shared_ptr<IDevice> graphicsDevice,
                                                            uint32_t outputWidth,
                                                            uint32_t outputHeight) {
        try {
            return std::make_shared<DLSSFactory>(configManager, graphicsDevice, outputWidth, outputHeight);
        } catch (FeatureNotSupported&) {
            return nullptr;
        }
    }

} // namespace toolkit::graphics
