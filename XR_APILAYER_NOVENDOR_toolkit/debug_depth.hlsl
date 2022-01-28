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

cbuffer config : register(b0) {
    float4x4 Unused1;
    float DepthScale;
};
SamplerState samplerLinearClamp : register(s0);

#ifndef VPRT
#define SAMPLE_TEXTURE(source, texcoord) source.Sample(samplerLinearClamp, (texcoord))
Texture2D sourceTexture : register(t0);
#else
#define SAMPLE_TEXTURE(source, texcoord) source.Sample(samplerLinearClamp, float3((texcoord), 0))
Texture2DArray sourceTexture : register(t0);
#endif

float4 main(in float4 position : SV_POSITION, in float2 texcoord : TEXCOORD0) : SV_TARGET {
    float4 inputColor = SAMPLE_TEXTURE(sourceTexture, texcoord);
    if (DepthScale > 0) {
        return float4(inputColor.xxx * DepthScale, 1);
    } else {
        return float4((1 - inputColor.xxx) * abs(DepthScale), 1);
    }
}
