//
// Created by Jacek on 20.03.2025.
//

#include <iostream>

#include "pixelbuffer.h"

PixelBuffer::PixelBuffer(int width, int height)
    : _width(width),
      _height(height),
      _pixels(width * height) {
}

void PixelBuffer::SetPixelColor(int x, int y, std::shared_ptr<Color> color) {
    _pixels[y * _width + x] = color;
}

Color PixelBuffer::GetPixel(int x, int y) const {
    return *_pixels[y * _width + x];
}

void PixelBuffer::SetAllPixels(std::shared_ptr<Color> color) {
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            SetPixelColor(x, y, color);
        }
    }
}

void PixelBuffer::DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, std::shared_ptr<Color> color) {

    int x11 = (int) ((x1+1) * _width * 0.5f);
    int y11 = (int) ((y1+1) * _height * 0.5f);

    int x22 = (int) ((x2+1) * _width * 0.5f);
    int y22 = (int) ((y2+1) * _height * 0.5f);

    int x33 = (int) ((x3+1) * _width * 0.5f);
    int y33 = (int) ((y3+1) * _height * 0.5f);

    int minX = std::min(x11, x22);
    minX = std::min(minX, x33);
    minX = std::max(minX, 0);

    int maxX = std::max(x11, x22);
    maxX = std::max(maxX, x33);
    maxX = std::min(maxX, _width - 1);

    int minY = std::min(y11, y22);
    minY = std::min(minY, y33);
    minY = std::max(minY, 0);

    int maxY = std::max(y11, y22);
    maxY = std::max(maxY, y33);
    maxX = std::min(maxX, _height - 1);

    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {
            if ((x11 - x22) * (y - y11) - (y11 - y22) * (x - x11) > 0 &&
                (x22 - x33) * (y - y22) - (y22 - y33) * (x - x22) > 0 &&
                (x33 - x11) * (y - y33) - (y33 - y11) * (x - x33) > 0) {
                    SetPixelColor(x, y, color);
                }
        }
    }
}
