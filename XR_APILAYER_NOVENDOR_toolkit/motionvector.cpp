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

#include "shader_utilities.h"
#include "factories.h"
#include "interfaces.h"
#include "layer.h"
#include "log.h"

namespace {

    using namespace toolkit;
    using namespace toolkit::graphics;
    using namespace toolkit::log;

    using namespace xr::math;

    __declspec(align(256)) struct MotionVectorConfig {
        DirectX::XMFLOAT4X4 ViewProjectionInverseMatrix;
        DirectX::XMFLOAT4X4 PreviousViewProjectionMatrix;
    };

    class MotionVectorProcessor : public IMotionVectorProcessor {
      public:
        MotionVectorProcessor(std::shared_ptr<IDevice> graphicsDevice) : m_device(graphicsDevice) {
            const auto shadersDir = dllHome / "shaders";
            const auto shaderPath = shadersDir / "motionvector.hlsl";
            m_shader = m_device->createQuadShader(
                shaderPath.string(), "main", "Motion Vector PS", nullptr, shadersDir.string());

            utilities::shader::Defines defines;
            defines.add("VPRT", true);
            m_shaderVPRT = m_device->createQuadShader(
                shaderPath.string(), "main", "Motion Vector VPRT PS", defines.get(), shadersDir.string());

            m_configBuffer = m_device->createBuffer(sizeof(MotionVectorConfig), "Motion Vector Configuration CB");
        }

        void process(const View& lastView,
                     const View& currentView,
                     std::shared_ptr<ITexture> depth,
                     std::shared_ptr<ITexture> output,
                     int32_t slice = -1) override {
            const DirectX::XMMATRIX projection[] = {
                xr::math::ComposeProjectionMatrix(lastView.fov, lastView.nearFar),
                xr::math::ComposeProjectionMatrix(currentView.fov, currentView.nearFar)};
            const DirectX::XMMATRIX view[] = {xr::math::LoadInvertedXrPose(lastView.pose),
                                              xr::math::LoadInvertedXrPose(currentView.pose)};

            const DirectX::XMMATRIX viewProjection[] = {
                view[0] * projection[0],
                view[1] * projection[1],
            };

            MotionVectorConfig staging;
            DirectX::XMStoreFloat4x4(&staging.ViewProjectionInverseMatrix,
                                     DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(nullptr, viewProjection[1])));
            DirectX::XMStoreFloat4x4(&staging.PreviousViewProjectionMatrix,
                                     DirectX::XMMatrixTranspose(viewProjection[0]));
            m_configBuffer->uploadData(&staging, sizeof(staging));

            // Run the shader.
            m_device->setShader(!depth->isArray() ? m_shader : m_shaderVPRT);
            m_device->setShaderInput(0, m_configBuffer);
            m_device->setShaderInput(0, depth, slice);
            m_device->setShaderOutput(0, output, slice);

            m_device->dispatchShader();
        }

      private:
        const std::shared_ptr<IDevice> m_device;

        std::shared_ptr<IQuadShader> m_shader;
        std::shared_ptr<IQuadShader> m_shaderVPRT;
        std::shared_ptr<IShaderBuffer> m_configBuffer;
    };

} // namespace

namespace toolkit::graphics {

    std::shared_ptr<IMotionVectorProcessor> CreateMotionVectorProcessor(std::shared_ptr<IDevice> graphicsDevice) {
        return std::make_shared<MotionVectorProcessor>(graphicsDevice);
    }

} // namespace toolkit::graphics
