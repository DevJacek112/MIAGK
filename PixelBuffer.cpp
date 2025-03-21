//
// Created by Jacek on 20.03.2025.
//

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

void PixelBuffer::DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, std::shared_ptr<Color> color) {
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            if ((x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0 &&
                (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0 &&
                (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0) {
                    SetPixelColor(x, y, color);
                }
        }
    }
}
