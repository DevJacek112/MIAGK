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

void PixelBuffer::DrawTriangle(float canonX1, float canonY1, std::shared_ptr<Color> color1,
                               float canonX2, float canonY2, std::shared_ptr<Color> color2,
                               float canonX3, float canonY3, std::shared_ptr<Color> color3) {
    int x1 = (int) ((canonX1 + 1) * _width * 0.5f);
    int y1 = (int) ((canonY1 + 1) * _height * 0.5f);

    int x2 = (int) ((canonX2 + 1) * _width * 0.5f);
    int y2 = (int) ((canonY2 + 1) * _height * 0.5f);

    int x3 = (int) ((canonX3 + 1) * _width * 0.5f);
    int y3 = (int) ((canonY3 + 1) * _height * 0.5f);

    int minX = std::min(x1, x2);
    minX = std::min(minX, x3);
    minX = std::max(minX, 0);

    int maxX = std::max(x1, x2);
    maxX = std::max(maxX, x3);
    maxX = std::min(maxX, _width - 1);

    int minY = std::min(y1, y2);
    minY = std::min(minY, y3);
    minY = std::max(minY, 0);

    int maxY = std::max(y1, y2);
    maxY = std::max(maxY, y3);
    maxY = std::min(maxY, _height - 1);

    int dy12 = y1 - y2;
    int dy23 = y2 - y3;
    int dy31 = y3 - y1;

    int dx12 = x1 - x2;
    int dx23 = x2 - x3;
    int dx31 = x3 - x1;

    bool tl1 = false;
    bool tl2 = false;
    bool tl3 = false;

    if (dy12 < 0 || (dy12 == 0 && dx12 > 0)) {
        tl1 = true;
    }

    if (dy23 < 0 || (dy23 == 0 && dx23 > 0)) {
        tl2 = true;
    }

    if (dy31 < 0 || (dy31 == 0 && dx31) > 0) {
        tl3 = true;
    }

    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {
            bool tl1BiggerThen0 = false;
            if (tl1) {
                tl1BiggerThen0 = (x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) >= 0;
            } else {
                tl1BiggerThen0 = (x1 - x2) * (y - y1) - (y1 - y2) * (x - x1) > 0;
            }

            bool tl2BiggerThen0 = false;
            if (tl2) {
                tl2BiggerThen0 = (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) >= 0;
            } else {
                tl2BiggerThen0 = (x2 - x3) * (y - y2) - (y2 - y3) * (x - x2) > 0;
            }

            bool tl3BiggerThen0 = false;
            if (tl3) {
                tl3BiggerThen0 = (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) >= 0;
            } else {
                tl3BiggerThen0 = (x3 - x1) * (y - y3) - (y3 - y1) * (x - x3) > 0;
            }

            if (tl1BiggerThen0 && tl2BiggerThen0 && tl3BiggerThen0) {
                Vector3 baricentricCoords = GetBaricentricTriangleCoords(x1, y1, x2, y2, x3, y3, x, y);

                std::shared_ptr<Color> finalColor = InterpolateColor(color1, color2, color3, baricentricCoords);
                SetPixelColor(x, y, finalColor);
            }
        }
    }
}

Vector3 PixelBuffer::GetBaricentricTriangleCoords(int x1, int y1, int x2, int y2, int x3, int y3, int actualX,
                                                  int actualY) {
    float denom = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3);

    float lambda1 = ((y2 - y3) * (actualX - x3) + (x3 - x2) * (actualY - y3)) / denom;
    float lambda2 = ((y3 - y1) * (actualX - x3) + (x1 - x3) * (actualY - y3)) / denom;
    float lambda3 = 1.0f - lambda1 - lambda2;

    return Vector3(lambda1, lambda2, lambda3);
}

std::shared_ptr<Color> PixelBuffer::InterpolateColor(std::shared_ptr<Color> c1, std::shared_ptr<Color> c2,
                                                     std::shared_ptr<Color> c3, Vector3 barycentricCoords) {
    float r = barycentricCoords.x * c1->_r + barycentricCoords.y * c2->_r + barycentricCoords.z * c3->_r;
    float g = barycentricCoords.x * c1->_g + barycentricCoords.y * c2->_g + barycentricCoords.z * c3->_g;
    float b = barycentricCoords.x * c1->_b + barycentricCoords.y * c2->_b + barycentricCoords.z * c3->_b;

    return std::make_shared<Color>(r, g, b, 0);
}
