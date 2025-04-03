//
// Created by Jacek on 20.03.2025.
//

#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <memory>
#include <vector>

#include "Color.h"

class PixelBuffer {
public:
    int _width;
    int _height;
    float _depth;
    std::vector<std::shared_ptr<Color>> _pixels;

    PixelBuffer(int width, int height);

    void SetPixelColor(int x, int y, std::shared_ptr<Color> color);
    Color GetPixel(int x, int y) const;

    void SetAllPixels(std::shared_ptr<Color> color);
    void DrawTriangle(float x1, float y1, float x2, float y2, float x3, float y3, std::shared_ptr<Color> color);

};

#endif // PIXELBUFFER_H
