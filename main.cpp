#include <iostream>
#include <memory>

#include "Color.h"
#include "PixelBuffer.h"
#include "TGAWriter.h"

int main() {

    std::shared_ptr<Color> red = std::make_shared<Color>(255, 0, 0, 122);
    std::shared_ptr<Color> green = std::make_shared<Color>(0, 255, 0, 122);
    std::shared_ptr<Color> blue = std::make_shared<Color>(0, 0, 255, 122);
    std::shared_ptr<Color> white = std::make_shared<Color>(255, 255, 255, 122);
    std::shared_ptr<Color> black = std::make_shared<Color>(0, 0, 0, 122);

    auto pixelBuffer = std::make_shared<PixelBuffer>(500, 500);

    pixelBuffer->SetAllPixelsColor(black);

    pixelBuffer->DrawTriangle(Vector3(0.9f, -0.9f, 0.0f),  blue, Vector3(-1.0f, -1.0f, 0.0f), blue, Vector3(1.0f, 1.0f, 0.0f), blue);
    pixelBuffer->DrawTriangle(Vector3(-0.5f, 0.0f, 1.0f),  green, Vector3(1.5f, 0.5f, -1.0f), green, Vector3(1.5f, -1.5f, -1.0f), green);
    pixelBuffer->DrawTriangle(Vector3(-0.9f, 0.9f, 0.0f), red, Vector3(1.0f, 1.0f, 0.0f), red, Vector3(-1.0f, -1.0f, 0.0f), red);

    TGAWriter::SaveToTGA("test.tga", pixelBuffer);

    return 0;
}





