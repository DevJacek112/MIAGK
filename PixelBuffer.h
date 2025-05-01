//
// Created by Jacek on 20.03.2025.
//

#ifndef PIXELBUFFER_H
#define PIXELBUFFER_H

#include <complex.h>
#include <complex.h>
#include <memory>
#include <vector>
#include <vector>
#include <vector>

#include "Color.h"
#include "Texture.h"
#include "Math/float3.h"

class PixelBuffer {
public:
    int _width;
    int _height;
    std::vector<std::shared_ptr<Color>> _pixelsColor;
    std::vector<float> _pixelsDepth;

    std::shared_ptr<Texture> tex1;
    bool isFirstTextureUsed = false;
    std::shared_ptr<Texture> tex2;


    PixelBuffer() = default;

    PixelBuffer(int width, int height);

    void SetPixelColor(int x, int y, std::shared_ptr<Color> color);
    Color GetPixelColor(int x, int y) const;

    void SetPixelDepth(int x, int y, float depth);
    float GetPixelDepth(int x, int y);

    void SetAllPixelsColor(std::shared_ptr<Color> color);

    void DrawTriangle(float3 canonV1, std::shared_ptr<Color> color1, float3 canonV2, std::shared_ptr<Color> color2, float3 canonV3, std::
                      shared_ptr<Color> color3, float3 uv1, float3 uv2, float3 uv3, int textureNumber, float3 normal1, float3 normal2, float3
                      normal3);

    float3 GetBaricentricTriangleCoords(int x1, int y1, int x2, int y2, int x3, int y3, int actualX, int actualY);

    std::shared_ptr<Color> InterpolateColor(std::shared_ptr<Color> c1, std::shared_ptr<Color> c2,
                                            std::shared_ptr<Color> c3, float3 barycentricCoords);

    Color SampleTexture(int textureNumber, float u, float v);
};

#endif // PIXELBUFFER_H
