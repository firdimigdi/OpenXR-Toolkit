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
        FrameAnalyzer(std::shared_ptr<IConfigManager> configManager,
                      std::shared_ptr<IDevice> graphicsDevice,
                      uint32_t displayWidth,
                      uint32_t displayHeight,
                      FrameAnalyzerHeuristic heuristic)
            : m_configManager(configManager), m_device(graphicsDevice), m_displayWidth(displayWidth),
              m_displayHeight(displayHeight), m_forceHeuristic(heuristic) {
        }

        void registerColorSwapchainImage(std::shared_ptr<ITexture> source, Eye eye) override {
            m_eyeSwapchainImages[(int)eye].insert(source->getNativePtr());
        }

        void resetForFrame() override {
            m_hasSeenLeftEye = m_hasSeenRightEye = false;
            m_hasCopiedLeftEye = m_hasCopiedRightEye = false;
            if (m_heuristic != FrameAnalyzerHeuristic::MultipleDepthBuffers) {
                m_leftEyeDepth = m_rightEyeDepth = nullptr;
            }

            m_eyePrediction = m_firstEye;
            m_isPredictionValid = m_shouldPredictEye;
        }

        void prepareForEndFrame() override {
            if (m_heuristic == FrameAnalyzerHeuristic::Unknown) {
                if (m_hasSeenLeftEye && m_hasSeenRightEye &&
                    (m_forceHeuristic == FrameAnalyzerHeuristic::ForwardRender ||
                     m_forceHeuristic == FrameAnalyzerHeuristic::Unknown)) {
                    Log("Detected forward rendering\n");
                    m_heuristic = FrameAnalyzerHeuristic::ForwardRender;
                    m_firstEye = Eye::Left;
                } else if (m_hasCopiedLeftEye && m_hasCopiedRightEye &&
                           (m_forceHeuristic == FrameAnalyzerHeuristic::DeferredCopy ||
                            m_forceHeuristic == FrameAnalyzerHeuristic::Unknown)) {
                    Log("Detected deferred rendering with copy\n");
                    m_heuristic = FrameAnalyzerHeuristic::DeferredCopy;
                    m_firstEye = m_firstEyeCopy;
                } else if (m_leftEyeDepth && m_rightEyeDepth &&
                           (m_forceHeuristic == FrameAnalyzerHeuristic::MultipleDepthBuffers ||
                            m_forceHeuristic == FrameAnalyzerHeuristic::Unknown)) {
                    Log("Fallback to depth buffer association\n");
                    m_heuristic = FrameAnalyzerHeuristic::MultipleDepthBuffers;
                    m_firstEye = Eye::Left;
                }

                TraceLoggingWrite(g_traceProvider, "TrySetHeuristic", TLArg((uint32_t)m_heuristic, "Heuristic"));

                m_shouldPredictEye = m_heuristic != FrameAnalyzerHeuristic::Unknown;
            }
        }

        void onSetRenderTarget(std::shared_ptr<graphics::IContext> context,
                               std::shared_ptr<ITexture> renderTarget) override {
            const auto& info = renderTarget->getInfo();
            if (info.arraySize != 1) {
                return;
            }

            const void* const nativePtr = renderTarget->getNativePtr();

            // Handle when the application uses the swapchain image directly.
            if (m_eyeSwapchainImages[0].find(nativePtr) != m_eyeSwapchainImages[0].cend()) {
                TraceLoggingWrite(g_traceProvider, "DetectedLeftEyeForwardRender");
                m_eyePrediction = Eye::Left;
                m_hasSeenLeftEye = true;
            } else if (m_eyeSwapchainImages[1].find(nativePtr) != m_eyeSwapchainImages[1].cend()) {
                TraceLoggingWrite(g_traceProvider, "DetectedRightEyeForwardRender");
                m_eyePrediction = Eye::Right;
                m_hasSeenRightEye = true;
            }
        }

        void onUnsetRenderTarget(std::shared_ptr<graphics::IContext> context) override {
        }

        void onSetDepthStencil(std::shared_ptr<ITexture> depthStencil) override {
            const auto& info = depthStencil->getInfo();
            if (info.arraySize != 1) {
                return;
            }

            const void* const nativePtr = depthStencil->getNativePtr();

            if (m_heuristic == FrameAnalyzerHeuristic::MultipleDepthBuffers) {
                if (nativePtr == m_leftEyeDepth) {
                    TraceLoggingWrite(g_traceProvider, "DetectedLeftEyeDepthBuffer");
                    m_eyePrediction = Eye::Left;
                } else if (nativePtr == m_rightEyeDepth) {
                    TraceLoggingWrite(g_traceProvider, "DetectedRightEyeDepthBuffer");
                    m_eyePrediction = Eye::Right;
                }
            } else if (m_heuristic == FrameAnalyzerHeuristic::Unknown) {
                // Record the first and second depth buffer seen for the image of our targer resolution. This is what
                // DCS needs.
                if (std::abs((int32_t)info.width - (int32_t)m_displayWidth) <= 4 &&
                    std::abs((int32_t)info.height - (int32_t)m_displayHeight) <= 4) {
                    if (!m_leftEyeDepth) {
                        m_leftEyeDepth = nativePtr;
                    } else if (!m_rightEyeDepth) {
                        m_rightEyeDepth = nativePtr;
                    }
                }
            }
        }

        void onUnsetDepthStencil(bool isDepthInverted) override {
        }

        void onCopyTexture(std::shared_ptr<ITexture> source,
                           std::shared_ptr<ITexture> destination,
                           int sourceSlice = -1,
                           int destinationSlice = -1) override {
            if (destination->getInfo().arraySize != 1) {
                return;
            }

            const void* const nativePtr = destination->getNativePtr();

            // Handle when the application copies the texture to the swapchain image mid-pass. This is what FS2020 does.
            if (m_eyeSwapchainImages[0].find(nativePtr) != m_eyeSwapchainImages[0].cend()) {
                TraceLoggingWrite(g_traceProvider, "DetectedLeftEyeCopyOut");

                if (!m_hasCopiedLeftEye && !m_hasCopiedRightEye) {
                    m_firstEyeCopy = Eye::Left;
                }

                // Switch to right eye now.
                m_eyePrediction = Eye::Right;
                m_hasCopiedLeftEye = true;
            } else if (m_eyeSwapchainImages[1].find(nativePtr) != m_eyeSwapchainImages[1].cend()) {
                TraceLoggingWrite(g_traceProvider, "DetectedRightEyeCopyOut");

                if (!m_hasCopiedLeftEye && !m_hasCopiedRightEye) {
                    m_firstEyeCopy = Eye::Right;
                }

                // Switch to left eye now.
                m_eyePrediction = Eye::Left;
                m_hasCopiedRightEye = true;
            }
        }

        std::optional<Eye> getEyeHint() const override {
            if (!m_isPredictionValid) {
                return std::nullopt;
            }
            return m_eyePrediction;
        }

      private:
        const std::shared_ptr<IConfigManager> m_configManager;
        const std::shared_ptr<IDevice> m_device;
        const uint32_t m_displayWidth;
        const uint32_t m_displayHeight;
        const FrameAnalyzerHeuristic m_forceHeuristic;

        std::set<const void*> m_eyeSwapchainImages[ViewCount];
        const void* m_leftEyeDepth{nullptr};
        const void* m_rightEyeDepth{nullptr};

        bool m_hasSeenLeftEye{false};
        bool m_hasSeenRightEye{false};
        bool m_hasCopiedLeftEye{false};
        bool m_hasCopiedRightEye{false};
        Eye m_firstEyeCopy;
        FrameAnalyzerHeuristic m_heuristic{FrameAnalyzerHeuristic::Unknown};

        bool m_shouldPredictEye{false};
        bool m_isPredictionValid{false};
        Eye m_eyePrediction;
        Eye m_firstEye{Eye::Left};
    };

} // namespace

namespace toolkit::graphics {
    std::shared_ptr<IFrameAnalyzer> CreateFrameAnalyzer(std::shared_ptr<IConfigManager> configManager,
                                                        std::shared_ptr<IDevice> graphicsDevice,
                                                        uint32_t displayWidth,
                                                        uint32_t displayHeight,
                                                        FrameAnalyzerHeuristic heuristic) {
        return std::make_shared<FrameAnalyzer>(configManager, graphicsDevice, displayWidth, displayHeight, heuristic);
    }

} // namespace toolkit::graphics
