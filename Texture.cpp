//
// Created by Jacek on 29.04.2025.
//

#include "Texture.h"


bool Texture::LoadFromTGA(const std::string& filename) {
    std::ifstream file(filename, std::ios::binary);
    if (!file) {
        std::cerr << "Nie mozna otworzyc pliku: " << filename << std::endl;
        return false;
    }

    unsigned char header[18];
    file.read(reinterpret_cast<char*>(header), sizeof(header));

    if (header[2] != 2) {
        std::cerr << "Nieobslugiwany typ obrazu (tylko nieskompresowane RGB): " << static_cast<int>(header[2]) << std::endl;
        return false;
    }

    if (header[16] != 24 && header[16] != 32) {
        std::cerr << "Nieobslugiwana glebokosc kolorow: " << static_cast<int>(header[16]) << " bpp" << std::endl;
        return false;
    }

    width = header[12] | (header[13] << 8);
    height = header[14] | (header[15] << 8);
    data.resize(width * height);

    int bytesPerPixel = header[16] / 8;

    for (int y = height - 1; y >= 0; --y) {
        for (int x = 0; x < width; ++x) {
            unsigned char pixel[4] = { 0, 0, 0, 255 }; // Domyślnie alfa = 255
            file.read(reinterpret_cast<char*>(pixel), bytesPerPixel);

            Color c(pixel[2], pixel[1], pixel[0], bytesPerPixel == 4 ? pixel[3] : 255);
            data[y * width + x] = c;
        }
    }

    file.close();
    return true;
}
