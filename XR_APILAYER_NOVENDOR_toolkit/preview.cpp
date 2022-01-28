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
    using namespace toolkit::graphics;
    using namespace toolkit::utilities;
    using namespace toolkit::log;

    constexpr uint32_t NumBuffers = 2;
    const auto WindowWidth = 1000;
    const auto WindowHeight = 1000;

    class PreviewWindow : public IPreviewWindow {
      public:
        PreviewWindow(const std::string& appName,
                      std::shared_ptr<IConfigManager> configManager,
                      std::shared_ptr<IDevice> device)
            : m_configManager(configManager), m_device(device) {
            g_instance = this;

            WNDCLASSEX wndClassEx = {sizeof(wndClassEx)};
            wndClassEx.lpfnWndProc = wndProcWrapper;
            wndClassEx.style = CS_HREDRAW | CS_VREDRAW;
            wndClassEx.lpszClassName = L"PreviewWindow";

            RegisterClassEx(&wndClassEx);

            m_hwnd = CreateWindow(wndClassEx.lpszClassName,
                                  std::wstring(appName.begin(), appName.end()).c_str(),
                                  WS_POPUP | WS_SYSMENU | WS_BORDER | WS_CAPTION | WS_MINIMIZEBOX,
                                  CW_USEDEFAULT,
                                  CW_USEDEFAULT,
                                  WindowWidth,
                                  WindowHeight,
                                  nullptr,
                                  nullptr,
                                  nullptr,
                                  nullptr);

            ComPtr<IUnknown> d3dDevice;
            ComPtr<IDXGIFactory2> dxgiFactory;
            if (m_device->getApi() == Api::D3D11) {
                d3dDevice = m_device->getNative<D3D11>();

                ComPtr<IDXGIDevice1> dxgiDevice;
                d3dDevice->QueryInterface(__uuidof(IDXGIDevice1), reinterpret_cast<void**>(dxgiDevice.GetAddressOf()));
                ComPtr<IDXGIAdapter> dxgiAdapter;
                dxgiDevice->GetAdapter(&dxgiAdapter);
                dxgiAdapter->GetParent(__uuidof(IDXGIFactory2), reinterpret_cast<void**>(dxgiFactory.GetAddressOf()));
            } else {
                throw new std::runtime_error("Unsupported graphics runtime");
            }

            {
                RECT rect = {0, 0, WindowWidth, WindowHeight};
                AdjustWindowRect(&rect, WS_POPUP, false);

                DXGI_SWAP_CHAIN_DESC1 desc;
                ZeroMemory(&desc, sizeof(desc));
                desc.Width = rect.right - rect.left;
                desc.Height = rect.bottom - rect.top;
                desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
                desc.SampleDesc.Count = 1;
                desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
                desc.BufferCount = NumBuffers;
                desc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
                dxgiFactory->CreateSwapChainForHwnd(d3dDevice.Get(), m_hwnd, &desc, nullptr, nullptr, set(m_swapchain));
            }

            ShowWindow(m_hwnd, SW_SHOW);
            UpdateWindow(m_hwnd);

            createSwapchain();
        }

        std::shared_ptr<ITexture> getRenderTarget() const {
            if (!m_renderTargets.size()) {
                return nullptr;
            }

            return m_renderTargets[m_currentBuffer];
        }

        void present() override {
            if (!m_renderTargets.size()) {
                return;
            }

            MSG msg;
            while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
                TranslateMessage(&msg);
                DispatchMessage(&msg);

                if (msg.message == WM_QUIT) {
                    m_renderTargets.clear();
                    return;
                }
            }
            m_swapchain->Present(0, 0);

            m_currentBuffer++;
            if (m_currentBuffer >= m_renderTargets.size()) {
                m_currentBuffer = 0;
            }
        }

      private:
        LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
            switch (msg) {
            case WM_SIZE:
                createSwapchain();
                break;

            case WM_DESTROY:
                PostQuitMessage(0);
                break;
            }

            return DefWindowProc(hwnd, msg, wParam, lParam);
        }

        void createSwapchain() {
            if (!m_swapchain) {
                return;
            }

            if (m_device->getApi() == Api::D3D11) {
                m_renderTargets.clear();
                CHECK_HRCMD(m_swapchain->ResizeBuffers(0, 0, 0, DXGI_FORMAT_UNKNOWN, 0));

                for (uint32_t i = 0; i < NumBuffers; i++) {
                    ComPtr<ID3D11Texture2D> frameBuffer;
                    m_swapchain->GetBuffer(
                        0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(frameBuffer.GetAddressOf()));

                    XrSwapchainCreateInfo info;
                    {
                        D3D11_TEXTURE2D_DESC desc;
                        frameBuffer->GetDesc(&desc);
                        info.width = desc.Width;
                        info.height = desc.Height;
                        info.arraySize = 1;
                        info.format = desc.Format;
                        info.mipCount = desc.MipLevels;
                        info.sampleCount = desc.SampleDesc.Count;
                        info.usageFlags = XR_SWAPCHAIN_USAGE_COLOR_ATTACHMENT_BIT;
                    }

                    m_renderTargets.push_back(WrapD3D11Texture(
                        m_device, info, frameBuffer.Get(), fmt::format("Preview Swapchain {} TEX2D", i)));
                }
            }
        }

        const std::shared_ptr<IConfigManager> m_configManager;
        const std::shared_ptr<IDevice> m_device;

        HWND m_hwnd{nullptr};
        ComPtr<IDXGISwapChain1> m_swapchain;
        std::vector<std::shared_ptr<ITexture>> m_renderTargets;
        uint32_t m_currentBuffer{0};

        static inline PreviewWindow* g_instance = nullptr;
        static LRESULT CALLBACK wndProcWrapper(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
            assert(g_instance);
            return g_instance->wndProc(hwnd, msg, wParam, lParam);
        }
    };

} // namespace

namespace toolkit::utilities {

    std::shared_ptr<IPreviewWindow> CreatePreviewWindow(const std::string& appName,
                                                        std::shared_ptr<IConfigManager> configManager,
                                                        std::shared_ptr<IDevice> device) {
        return std::make_shared<PreviewWindow>(appName, configManager, device);
    }

} // namespace toolkit::utilities
