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
#include "log.h"

namespace {

    using namespace toolkit;
    using namespace toolkit::config;
    using namespace toolkit::log;
    using namespace toolkit::graphics;
    using namespace toolkit::utilities;

    class FrameAnalyzer : public IFrameAnalyzer {
      public:
        FrameAnalyzer(std::shared_ptr<IConfigManager> configManager, std::shared_ptr<IDevice> graphicsDevice)
            : m_configManager(configManager), m_device(graphicsDevice) {
        }

        void registerColorSwapchainImage(XrSwapchain swapchain, std::shared_ptr<ITexture> source, Eye eye) override {
            m_eyeSwapchainImages[(int)eye].insert_or_assign(source->getNativePtr(), swapchain);
        }

        void registerFinishPassEvent(FinishPassEvent event) override {
            m_finishPassEvent = event;
        }

        void resetForFrame() override {
            // Assumes left eye is first in case we won't be able to tell for sure.
            m_eyePrediction = Eye::Left;
            m_isPredictionValid = m_shouldPredictEye;

            for (uint32_t i = 0; i < ViewCount; i++) {
                m_depthStencilForEye[i].reset();
            }
        }

        void prepareForEndFrame() override {
            onUnsetRenderTarget();
        }

        void onSetRenderTarget(std::shared_ptr<ITexture> renderTarget) override {
            // Flush previous render target if needed.
            onUnsetRenderTarget();

            if (renderTarget->getInfo().arraySize != 1) {
                return;
            }

            const void* const nativePtr = renderTarget->getNativePtr();

            // Handle when the application uses the swapchain image directly.
            {
                const auto& it = m_eyeSwapchainImages[0].find(nativePtr);
                if (it != m_eyeSwapchainImages[0].cend()) {
                    DebugLog("Detected setting RTV to left eye\n");
                    m_eyePrediction = Eye::Left;

                    // We are confident our prediction is accurate.
                    m_shouldPredictEye = true;

                    m_currentSwapchain = it->second;

                    return;
                }
            }
            {
                const auto& it = m_eyeSwapchainImages[1].find(nativePtr);
                if (it != m_eyeSwapchainImages[1].cend()) {
                    DebugLog("Detected setting RTV to right eye\n");
                    m_eyePrediction = Eye::Right;

                    // We are confident our prediction is accurate.
                    m_shouldPredictEye = true;

                    m_currentSwapchain = it->second;

                    return;
                }
            }
        }

        void onUnsetRenderTarget() override {
            if (m_currentSwapchain != XR_NULL_HANDLE) {
                if (m_isPredictionValid && m_finishPassEvent) {
                    m_finishPassEvent(m_currentSwapchain, m_eyePrediction);
                }

                m_currentSwapchain = XR_NULL_HANDLE;
            }
        }

        void onSetDepthStencil(std::shared_ptr<ITexture> depthStencil) override {
            if (!m_isPredictionValid) {
                return;
            }

            m_depthStencilForEye[(int)m_eyePrediction] = depthStencil;
        }

        void onUnsetDepthStencil(bool isDepthInverted) override {
            if (!m_isPredictionValid || !m_depthStencilForEye[(int)m_eyePrediction]) {
                return;
            }

            m_isDepthStencilForEyeInverted[(int)m_eyePrediction] = isDepthInverted;
        }

        void onCopyTexture(std::shared_ptr<ITexture> source,
                           std::shared_ptr<ITexture> destination,
                           int sourceSlice = -1,
                           int destinationSlice = -1) override {
            if (destination->getInfo().arraySize != 1) {
                return;
            }

            const void* const nativePtr = destination->getNativePtr();

            // Handle when the application copies the texture to the swapchain image mid-pass. Assumes left eye is
            // always first. This is what FS2020 does.
            {
                const auto& it = m_eyeSwapchainImages[0].find(nativePtr);
                if (it != m_eyeSwapchainImages[0].cend()) {
                    DebugLog("Detected copy-out to left eye\n");

                    // Switch to right eye now.
                    m_eyePrediction = Eye::Right;

                    // We are confident our prediction is accurate.
                    m_shouldPredictEye = true;

                    if (m_isPredictionValid && m_finishPassEvent) {
                        m_finishPassEvent(it->second, Eye::Left);
                    }

                    return;
                }
            }
            {
                const auto& it = m_eyeSwapchainImages[1].find(nativePtr);
                if (it != m_eyeSwapchainImages[1].cend()) {
                    DebugLog("Detected copy-out to right eye\n");

                    if (m_isPredictionValid && m_finishPassEvent) {
                        m_finishPassEvent(it->second, Eye::Right);
                    }

                    return;
                }
            }
        }

        std::optional<Eye> getEyeHint() const override {
            if (!m_isPredictionValid) {
                return std::nullopt;
            }
            return m_eyePrediction;
        }

        std::pair<std::shared_ptr<ITexture>, bool> getEyeDepthStencil(utilities::Eye eye) const override {
            if (!m_isPredictionValid) {
                return std::make_pair(nullptr, false);
            }
            return std::make_pair(m_depthStencilForEye[(int)eye], m_isDepthStencilForEyeInverted[(int)eye]);
        }

      private:
        const std::shared_ptr<IConfigManager> m_configManager;
        const std::shared_ptr<IDevice> m_device;

        FinishPassEvent m_finishPassEvent;

        std::map<const void*, XrSwapchain> m_eyeSwapchainImages[ViewCount];

        bool m_shouldPredictEye{false};
        bool m_isPredictionValid{false};
        Eye m_eyePrediction;

        XrSwapchain m_currentSwapchain{XR_NULL_HANDLE};
        std::shared_ptr<ITexture> m_depthStencilForEye[ViewCount];
        bool m_isDepthStencilForEyeInverted[ViewCount];
    };

} // namespace

namespace toolkit::graphics {
    std::shared_ptr<IFrameAnalyzer> CreateFrameAnalyzer(std::shared_ptr<IConfigManager> configManager,
                                                        std::shared_ptr<IDevice> graphicsDevice) {
        return std::make_shared<FrameAnalyzer>(configManager, graphicsDevice);
    }

} // namespace toolkit::graphics
