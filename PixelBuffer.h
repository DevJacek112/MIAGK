//
// Created by Jacek on 20.03.2025.
//

#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H
#include <fstream>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "Color.h"

class PixelBuffer {

public:

    int _width = 0;
    int _height = 0;
    float _depth = 0;
    std::vector<std::shared_ptr<Color>> _pixels;

    PixelBuffer(int width, int height, std::shared_ptr<Color> color)
        : _width(width),
          _height(height),
          _pixels(width * height, color){
    }

    void SetPixelColor(int x, int y, std::shared_ptr<Color> color) {
        _pixels[y * _width + x] = color;
    }

    Color GetPixel(int x, int y) const {
        return *_pixels[y * _width + x];
    }

    void SetAllPixels(std::shared_ptr<Color> color) {
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                SetPixelColor(x, y, color);
            }
        }
    }

};



#endif //PIXELBUFFER_H
