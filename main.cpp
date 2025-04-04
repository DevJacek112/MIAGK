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

    pixelBuffer->SetAllPixels(black);


    pixelBuffer->DrawTriangle(0.9f, -0.9f, blue, -1.0f, -1.0f, blue, 1.0f, 1.0f, blue);
    pixelBuffer->DrawTriangle(-0.9f, 0.9f, red, 1.0f, 1.0f, red, -1.0f, -1.0f, red);

    TGAWriter::SaveToTGA("test.tga", pixelBuffer);

    return 0;
}





