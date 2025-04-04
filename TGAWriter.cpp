//
// Created by Jacek on 20.03.2025.
//

#include <fstream>

#include "tgawriter.h"

void TGAWriter::SaveToTGA(const std::string& filename, std::shared_ptr<PixelBuffer> pixelBuffer) {
    std::ofstream file(filename, std::ios::binary);
    if (!file) {
        return;
    }

    unsigned char header[18] = { 0 };
    header[2] = 2;
    header[12] = pixelBuffer->_width & 0xFF;
    header[13] = (pixelBuffer->_width >> 8) & 0xFF;
    header[14] = pixelBuffer->_height & 0xFF;
    header[15] = (pixelBuffer->_height >> 8) & 0xFF;
    header[16] = 24;

    file.write(reinterpret_cast<char*>(header), sizeof(header));

    for (int y = pixelBuffer->_height - 1; y >= 0; --y) {
        for (int x = 0; x < pixelBuffer->_width; ++x) {
            const Color& color = pixelBuffer->GetPixel(x, pixelBuffer->_height - 1 - y);
            unsigned char pixel[3] = {
                static_cast<unsigned char>(color._b),
                static_cast<unsigned char>(color._g),
                static_cast<unsigned char>(color._r)
            };
            file.write(reinterpret_cast<char*>(pixel), sizeof(pixel));
        }
    }

    file.close();
}
