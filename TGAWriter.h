//
// Created by Jacek on 20.03.2025.
//

#ifndef TGAWRITER_H
#define TGAWRITER_H
#include <fstream>
#include <memory>
#include <string>

#include "PixelBuffer.h"


class TGAWriter {

public:
    void SaveToTGA(const std::string& filename, std::shared_ptr<PixelBuffer> pixelBuffer) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            return;
        }

        // Nagłówek pliku TGA (18 bajtów)
        unsigned char header[18] = { 0 };
        header[2] = 2; // Typ obrazu: bez kompresji, true-color
        header[12] = pixelBuffer->_width & 0xFF;
        header[13] = (pixelBuffer->_width >> 8) & 0xFF;
        header[14] = pixelBuffer->_height & 0xFF;
        header[15] = (pixelBuffer->_height >> 8) & 0xFF;
        header[16] = 24; // 24 bity na piksel (RGB)

        file.write(reinterpret_cast<char*>(header), sizeof(header));

        // Zapis pikseli w formacie BGR (TGA używa formatu BGR)
        for (int y = pixelBuffer->_height - 1; y >= 0; --y) { // TGA zapisuje obraz od dolnego wiersza
            for (int x = 0; x < pixelBuffer->_width; ++x) {
                const Color& color = pixelBuffer->GetPixel(x, y);
                unsigned char pixel[3] = {
                    static_cast<unsigned char>(color._b), // B
                    static_cast<unsigned char>(color._g), // G
                    static_cast<unsigned char>(color._r)  // R
                };
                file.write(reinterpret_cast<char*>(pixel), sizeof(pixel));
            }
        }

        file.close();
    }

};



#endif //TGAWRITER_H
