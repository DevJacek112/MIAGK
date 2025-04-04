//
// Created by Jacek on 20.03.2025.
//

#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <memory>
#include <vector>

#include "Color.h"
#include "Math/Vector3.h"

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

    void DrawTriangle(float canonX1, float canonY1, std::shared_ptr<Color> color1,
                      float canonX2, float canonY2, std::shared_ptr<Color> color2,
                      float canonX3, float canonY3, std::shared_ptr<Color> color3);

    Vector3 GetBaricentricTriangleCoords(int x1, int y1, int x2, int y2, int x3, int y3, int actualX, int actualY);

    std::shared_ptr<Color> InterpolateColor(std::shared_ptr<Color> c1, std::shared_ptr<Color> c2,
                                            std::shared_ptr<Color> c3, Vector3 barycentricCoords);
};

#endif // PIXELBUFFER_H
