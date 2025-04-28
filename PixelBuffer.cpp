//
// Created by Jacek on 20.03.2025.
//

#include <iostream>
#include <limits>

#include "pixelbuffer.h"
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"

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

void PixelBuffer::DrawTrianglePerVertexLight(float3 canonV1, std::shared_ptr<Color> color1, float3 canonV2,
                               std::shared_ptr<Color> color2, float3 canonV3, std::shared_ptr<Color> color3) {
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

                std::shared_ptr<Color> finalColor = InterpolateColor(color1, color2, color3, baricentricCoords);

                float depth = (baricentricCoords.x * v1.z + baricentricCoords.y * v2.z + baricentricCoords.z * v3.z);

                if (depth > GetPixelDepth(x, y)) {
                    SetPixelColor(x, y, finalColor);
                    SetPixelDepth(x, y, depth);
                }
            }
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

void PixelBuffer::DrawTrianglePerPixelLight(
    float3 canonV1, std::shared_ptr<Color> color1, float3 canonV2, std::shared_ptr<Color> color2,
    float3 canonV3, std::shared_ptr<Color> color3,
    const std::vector<PointLight>& pointLights,
    DirectionalLight directional,
    float4x4 world2view,
    const float3& worldPos1, const float3& worldPos2, const float3& worldPos3,
    const float3& normal1, const float3& normal2, const float3& normal3
) {
    float3 v1 = float3((canonV1.x + 1) * _width * 0.5f, (canonV1.y + 1) * _height * 0.5f, canonV1.z);
    float3 v2 = float3((canonV2.x + 1) * _width * 0.5f, (canonV2.y + 1) * _height * 0.5f, canonV2.z);
    float3 v3 = float3((canonV3.x + 1) * _width * 0.5f, (canonV3.y + 1) * _height * 0.5f, canonV3.z);

    float area = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
    if (area > 0) {
        std::swap(v2, v3);
        std::swap(color2, color3);
    }

    float minX = std::max(std::min({v1.x, v2.x, v3.x}), 0.0f);
    float maxX = std::min(std::max({v1.x, v2.x, v3.x}), (float)(_width - 1));
    float minY = std::max(std::min({v1.y, v2.y, v3.y}), 0.0f);
    float maxY = std::min(std::max({v1.y, v2.y, v3.y}), (float)(_height - 1));

    int dy12 = v1.y - v2.y;
    int dy23 = v2.y - v3.y;
    int dy31 = v3.y - v1.y;
    int dx12 = v1.x - v2.x;
    int dx23 = v2.x - v3.x;
    int dx31 = v3.x - v1.x;

    bool tl1 = dy12 < 0 || (dy12 == 0 && dx12 > 0);
    bool tl2 = dy23 < 0 || (dy23 == 0 && dx23 > 0);
    bool tl3 = dy31 < 0 || (dy31 == 0 && dx31 > 0);

    for (int y = minY; y <= maxY; ++y) {
        for (int x = minX; x <= maxX; ++x) {
            bool inside = true;

            inside &= ((v1.x - v2.x) * (y - v1.y) - (v1.y - v2.y) * (x - v1.x)) > (tl1 ? -1 : 0);
            inside &= ((v2.x - v3.x) * (y - v2.y) - (v2.y - v3.y) * (x - v2.x)) > (tl2 ? -1 : 0);
            inside &= ((v3.x - v1.x) * (y - v3.y) - (v3.y - v1.y) * (x - v3.x)) > (tl3 ? -1 : 0);

            if (inside) {
                float3 bary = GetBaricentricTriangleCoords(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, x, y);

                float3 interpWorldPos = bary.x * worldPos1 + bary.y * worldPos2 + bary.z * worldPos3;
                float3 interpNormal = (bary.x * normal1 + bary.y * normal2 + bary.z * normal3).GetNormalized();

                std::shared_ptr<Color> interpColor = InterpolateColor(color1, color2, color3, bary);

                std::shared_ptr<Color> finalColor = std::make_shared<Color>(0, 0, 0, 255);

                for (const auto& light : pointLights) {
                    auto lightContribution = light.calculatePhongLighting(interpWorldPos, interpNormal, interpColor,
                                                                          32.0f, 1.0f, 1.0f, 1.0f);

                    finalColor->_r = std::min(255, finalColor->_r + lightContribution->_r);
                    finalColor->_g = std::min(255, finalColor->_g + lightContribution->_g);
                    finalColor->_b = std::min(255, finalColor->_b + lightContribution->_b);
                }

                auto color2 = directional.calculatePhongLighting(
                    world2view,
                    interpWorldPos,
                    interpNormal,
                    interpColor,
                    32.0f, 1.0f, 1.0f, 1.0f
                );

                finalColor->_r = std::min(255, finalColor->_r + color2->_r);
                finalColor->_g = std::min(255, finalColor->_g + color2->_g);
                finalColor->_b = std::min(255, finalColor->_b + color2->_b);

                float depth = bary.x * v1.z + bary.y * v2.z + bary.z * v3.z;

                if (depth > GetPixelDepth(x, y)) {
                    SetPixelColor(x, y, finalColor);
                    SetPixelDepth(x, y, depth);
                }
            }
        }
    }
}