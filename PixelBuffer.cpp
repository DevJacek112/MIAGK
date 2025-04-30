//
// Created by Jacek on 20.03.2025.
//

#include <iostream>
#include <limits>

#include "pixelbuffer.h"

struct TexCoord {
    float u;
    float v;
};

PixelBuffer::PixelBuffer(int width, int height)
    : _width(width),
      _height(height),
      _pixelsColor(width * height),
      _pixelsDepth(width * height) {
        for (int y = 0; y < _height; ++y) {
            for (int x = 0; x < _width; ++x) {
                SetPixelColor(x, y, std::make_shared<Color>(0, 0, 0, 122));
                SetPixelDepth(x, y, -std::numeric_limits<float>::infinity());
            }
        }
}

void PixelBuffer::SetPixelColor(int x, int y, std::shared_ptr<Color> color) {
    _pixelsColor[y * _width + x] = color;
}

Color PixelBuffer::GetPixelColor(int x, int y) const {
    return *_pixelsColor[y * _width + x];
}

void PixelBuffer::SetPixelDepth(int x, int y, float depth) {
    _pixelsDepth[y * _width + x] = depth;
}

float PixelBuffer::GetPixelDepth(int x, int y) {
    return _pixelsDepth[y * _width + x];
}

void PixelBuffer::SetAllPixelsColor(std::shared_ptr<Color> color) {
    for (int y = 0; y < _height; ++y) {
        for (int x = 0; x < _width; ++x) {
            SetPixelColor(x, y, color);
        }
    }
}

float3 PixelBuffer::GetBaricentricTriangleCoords(int x1, int y1, int x2, int y2, int x3, int y3, int actualX,
                                                  int actualY) {
    float denom = (y2 - y3) * (x1 - x3) + (x3 - x2) * (y1 - y3);

    float lambda1 = ((y2 - y3) * (actualX - x3) + (x3 - x2) * (actualY - y3)) / denom;
    float lambda2 = ((y3 - y1) * (actualX - x3) + (x1 - x3) * (actualY - y3)) / denom;
    float lambda3 = 1.0f - lambda1 - lambda2;

    return float3(lambda1, lambda2, lambda3);
}

std::shared_ptr<Color> PixelBuffer::InterpolateColor(std::shared_ptr<Color> c1, std::shared_ptr<Color> c2,
                                                     std::shared_ptr<Color> c3, float3 barycentricCoords) {
    float r = barycentricCoords.x * c1->_r + barycentricCoords.y * c2->_r + barycentricCoords.z * c3->_r;
    float g = barycentricCoords.x * c1->_g + barycentricCoords.y * c2->_g + barycentricCoords.z * c3->_g;
    float b = barycentricCoords.x * c1->_b + barycentricCoords.y * c2->_b + barycentricCoords.z * c3->_b;

    return std::make_shared<Color>(r, g, b, 0);
}

Color PixelBuffer::SampleTexture(int textureNumber, float u, float v) {
    int texX, texY;
    if (textureNumber == 1) {
        texX = std::clamp(int(u * tex1->width), 0, tex1->width - 1);
        texY = std::clamp(int(v * tex1->height), 0, tex1->height - 1);
        return tex1->data[texY * tex1->width + texX];
    }
    if (textureNumber == 2) {
        texX = std::clamp(int(u * tex2->width), 0, tex2->width - 1);
        texY = std::clamp(int(v * tex2->height), 0, tex2->height - 1);
        return tex2->data[texY * tex2->width + texX];
    }
    return Color(255, 255, 255, 255);
}

void PixelBuffer::DrawTriangle(
    float3 canonV1, std::shared_ptr<Color> color1,
    float3 canonV2, std::shared_ptr<Color> color2,
    float3 canonV3, std::shared_ptr<Color> color3,
    float3 uv1, float3 uv2, float3 uv3,
    int textureNumber
) {
    float3 v1 = float3((canonV1.x + 1) * _width * 0.5f,
                         (canonV1.y + 1) * _height * 0.5f,
                         canonV1.z);

    float3 v2 = float3((canonV2.x + 1) * _width * 0.5f,
                         (canonV2.y + 1) * _height * 0.5f,
                         canonV2.z);

    float3 v3 = float3((canonV3.x + 1) * _width * 0.5f,
                         (canonV3.y + 1) * _height * 0.5f,
                         canonV3.z);

    float area = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
    if (area > 0) {
        std::swap(v2, v3);
        std::swap(color2, color3);
    }

    float minX = std::min(v1.x, v2.x);
    minX = std::min(minX, v3.x);
    minX = std::max(minX, 0.0f);

    float maxX = std::max(v1.x, v2.x);
    maxX = std::max(maxX, v3.x);
    maxX = std::min(maxX, (float) _width - 1);

    float minY = std::min(v1.y, v2.y);
    minY = std::min(minY, v3.y);
    minY = std::max(minY, 0.0f);

    float maxY = std::max(v1.y, v2.y);
    maxY = std::max(maxY, v3.y);
    maxY = std::min(maxY, (float) _height - 1);

    int dy12 = v1.y - v2.y;
    int dy23 = v2.y - v3.y;
    int dy31 = v3.y - v1.y;

    int dx12 = v1.x - v2.x;
    int dx23 = v2.x - v3.x;
    int dx31 = v3.x - v1.x;

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
            //rozne warunki w zaleznosci od tego czy krawedz jest lewa albo gorna
            bool tl1BiggerThen0 = false;
            if (tl1) {
                tl1BiggerThen0 = (v1.x - v2.x) * (y - v1.y) - (v1.y - v2.y) * (x - v1.x) >= 0;
            } else {
                tl1BiggerThen0 = (v1.x - v2.x) * (y - v1.y) - (v1.y - v2.y) * (x - v1.x) > 0;
            }

            bool tl2BiggerThen0 = false;
            if (tl2) {
                tl2BiggerThen0 = (v2.x - v3.x) * (y - v2.y) - (v2.y - v3.y) * (x - v2.x) >= 0;
            } else {
                tl2BiggerThen0 = (v2.x - v3.x) * (y - v2.y) - (v2.y - v3.y) * (x - v2.x) > 0;
            }

            bool tl3BiggerThen0 = false;
            if (tl3) {
                tl3BiggerThen0 = (v3.x - v1.x) * (y - v3.y) - (v3.y - v1.y) * (x - v3.x) >= 0;
            } else {
                tl3BiggerThen0 = (v3.x - v1.x) * (y - v3.y) - (v3.y - v1.y) * (x - v3.x) > 0;
            }

            //sprawdzenie czy piksele w trojkacie
            if (tl1BiggerThen0 && tl2BiggerThen0 && tl3BiggerThen0) {
                float3 baricentricCoords = GetBaricentricTriangleCoords(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, x, y);

                std::shared_ptr<Color> vertexColor = InterpolateColor(color1, color2, color3, baricentricCoords);

                // interpolacja UV
                float u = baricentricCoords.x * uv1.x + baricentricCoords.y * uv2.x + baricentricCoords.z * uv3.x;
                float v = baricentricCoords.x * uv1.y + baricentricCoords.y * uv2.y + baricentricCoords.z * uv3.y;

                Color texColor = SampleTexture(textureNumber, u, v);

                // moduluje kolor teksturą
                int r = (vertexColor->_r * texColor._r /255);
                int g = (vertexColor->_g * texColor._g /255);
                int b = (vertexColor->_b * texColor._b /255);

                float depth = baricentricCoords.x * v1.z + baricentricCoords.y * v2.z + baricentricCoords.z * v3.z;

                if (depth > GetPixelDepth(x, y)) {
                    SetPixelColor(x, y, std::make_shared<Color>(r, g, b, 255));
                    SetPixelDepth(x, y, depth);
                }
            }
        }
    }
}
