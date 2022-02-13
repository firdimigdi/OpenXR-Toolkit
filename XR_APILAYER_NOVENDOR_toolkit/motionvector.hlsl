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
    float4x4 ViewProjectionInverseMatrix;
    float4x4 PreviousViewProjectionMatrix;
};
SamplerState samplerLinearClamp : register(s0);

#ifndef VPRT
#define SAMPLE_TEXTURE(source, texcoord) source.Sample(samplerLinearClamp, (texcoord))
Texture2D depthBuffer : register(t0);
#else
#define SAMPLE_TEXTURE(source, texcoord) source.Sample(samplerLinearClamp, float3((texcoord), 0))
Texture2DArray depthBuffer : register(t0);
#endif

// See GPU Gems 3, Chapter 27.
// https://developer.nvidia.com/gpugems/gpugems3/part-iv-image-effects/chapter-27-motion-blur-post-processing-effect
float4 main(in float4 position : SV_POSITION, in float2 uv : TEXCOORD0) : SV_TARGET {
    // Get viewport position at this pixel.
    float4 currentClipPos;
    currentClipPos.x = uv.x * 2 - 1;
    currentClipPos.y = 1 - uv.y * 2;
    currentClipPos.z = SAMPLE_TEXTURE(depthBuffer, uv.xy).x;
    currentClipPos.w = 1;

    // Transform by the view-projection inverse.
    float4 worldPos = mul(currentClipPos, ViewProjectionInverseMatrix);

    // Divide by w to get the world position.
    if (worldPos.w <= 0)
        return 0;
    worldPos /= worldPos.w;

    // Use the world position, and transform by the previous view-projection matrix.
    float4 previousClipPos = mul(worldPos, PreviousViewProjectionMatrix);
    // Convert to non-homogeneous points by dividing by w.
    if (previousClipPos.w <= 0)
        return 0;
    previousClipPos /= previousClipPos.w;

    // Use this frame's position and last frame's to compute the pixel velocity.
    float2 velocity = (currentClipPos - previousClipPos) / 2.f;

    return float4(velocity, 0, 0);
}
