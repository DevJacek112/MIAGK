#include <iostream>
#include <memory>

#include "Camera.h"
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

    float3 v1(-1, -1, -5);
    float3 v2(0, 1, -5);
    float3 v3(1, -1, -5);

    Triangle triangle(v1,v2,v3, blue, blue, blue);

    Camera camera;
    camera.setPerspective(90.0f, 1.0f, 0.1f, 100.0f);
    camera.SetPixelBuffer(pixelBuffer);
    camera.RenderTriangle(triangle);

    TGAWriter::SaveToTGA("test.tga", pixelBuffer);

    return 0;
}





