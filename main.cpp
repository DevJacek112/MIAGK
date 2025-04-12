#include <iostream>
#include <memory>

#include "Color.h"
#include "PixelBuffer.h"
#include "TGAWriter.h"
#include "Math/float4x4.h"

int main() {

    std::shared_ptr<Color> red = std::make_shared<Color>(255, 0, 0, 122);
    std::shared_ptr<Color> green = std::make_shared<Color>(0, 255, 0, 122);
    std::shared_ptr<Color> blue = std::make_shared<Color>(0, 0, 255, 122);
    std::shared_ptr<Color> white = std::make_shared<Color>(255, 255, 255, 122);
    std::shared_ptr<Color> black = std::make_shared<Color>(0, 0, 0, 122);

    auto pixelBuffer = std::make_shared<PixelBuffer>(500, 500);

    pixelBuffer->SetAllPixelsColor(black);

    //ZADANIE 5
    float fovY = 90.0f * (3.14159265f / 180.0f);
    float f = 1.0f / tanf(fovY / 2.0f);
    float aspect = 1.0f;
    float nearZ = 0.1f;
    float farZ = 100.0f;

    float4 col0 = float4(f / aspect, 0.0f, 0.0f, 0.0f);
    float4 col1 = float4(0.0f, f, 0.0f, 0.0f);
    float4 col2 = float4(0.0f, 0.0f, (farZ + nearZ) / (nearZ - farZ), -1.0f);
    float4 col3 = float4(0.0f, 0.0f, (2 * farZ * nearZ) / (nearZ - farZ), 0.0f);

    float4x4 projectionMatrix = float4x4(col0, col1, col2, col3);

    float3 v1(-1, -1, -5);
    float3 v2(0, 1, -5);
    float3 v3(1, -1, -5);

    float4 v1_clip = projectionMatrix * float4(v1.x, v1.y, v1.z, 1.0f);
    float4 v2_clip = projectionMatrix * float4(v2.x, v2.y, v2.z, 1.0f);
    float4 v3_clip = projectionMatrix * float4(v3.x, v3.y, v3.z, 1.0f);

    float3 v1_ndc = float3((v1_clip.x / v1_clip.w), (v1_clip.y / v1_clip.w), (v1_clip.z / v1_clip.w));
    float3 v2_ndc = float3((v2_clip.x / v2_clip.w), (v2_clip.y / v2_clip.w), (v2_clip.z / v2_clip.w));
    float3 v3_ndc = float3((v3_clip.x / v3_clip.w), (v3_clip.y / v3_clip.w), (v3_clip.z / v3_clip.w));

    pixelBuffer->DrawTriangle(v1_ndc,  blue, v2_ndc, blue, v3_ndc, blue);
    //

    TGAWriter::SaveToTGA("test.tga", pixelBuffer);

    return 0;
}





