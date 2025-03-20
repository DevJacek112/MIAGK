#include <iostream>
#include <memory>

#include "Color.h"
#include "PixelBuffer.h"
#include "TGAWriter.h"

int main() {
    std::shared_ptr<Color> colors[3] {
        std::make_shared<Color>(255, 0, 0, 122),
        std::make_shared<Color>(0, 255, 0, 122),
        std::make_shared<Color>(0, 0, 255, 122)
    };

    TGAWriter writer;

    auto pixelBuffer = std::make_shared<PixelBuffer>(500, 100, colors[1]);


    pixelBuffer->SetAllPixels(colors[1]);
    pixelBuffer->SetPixelColor(1, 0, colors[0]);
    std::cout << pixelBuffer->GetPixel(2,2)._g << std::endl;
    std::cout << pixelBuffer->GetPixel(1,0)._r << std::endl;

    writer.SaveToTGA("test.tga", pixelBuffer);

    return 0;
}
