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

    pixelBuffer->SetAllPixels(blue);

    //pixelBuffer->DrawTriangle(125, 125, 0, 0, 0, 250, red);

    pixelBuffer->DrawTriangle(1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 1.0f, green);
    pixelBuffer->DrawTriangle(-1.0f, -1.0f, 0.0f, 1.0f, 1.0f, -1.0f, red);
    pixelBuffer->DrawTriangle(-1.0f, 1.0f, 0.0f, 1.0f, -1.0f, -1.0f, black);

    TGAWriter::SaveToTGA("test.tga", pixelBuffer);

    return 0;
}





