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
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Math/float3.h"

class PixelBuffer {
public:
    int _width;
    int _height;
    std::vector<std::shared_ptr<Color>> _pixelsColor;
    std::vector<float> _pixelsDepth;

    PixelBuffer() = default;

    PixelBuffer(int width, int height);

    void SetPixelColor(int x, int y, std::shared_ptr<Color> color);
    Color GetPixelColor(int x, int y) const;

    void SetPixelDepth(int x, int y, float depth);
    float GetPixelDepth(int x, int y);

    void SetAllPixelsColor(std::shared_ptr<Color> color);

    void DrawTrianglePerVertexLight(float3 canonV1, std::shared_ptr<Color> color1, float3 canonV2, std::shared_ptr<Color> color2, float3 canonV3, std::shared_ptr<Color> color3);

    float3 GetBaricentricTriangleCoords(int x1, int y1, int x2, int y2, int x3, int y3, int actualX, int actualY);

    std::shared_ptr<Color> InterpolateColor(std::shared_ptr<Color> c1, std::shared_ptr<Color> c2,
                                            std::shared_ptr<Color> c3, float3 barycentricCoords);

    float3 InterpolateNormal(float3 n1, float3 n2, float3 n3, float3 barycentricCoords);

    Color CalculateLighting(const float3 &position, const float3 &normal, const std::vector<PointLight> &lights);

    void DrawTrianglePerPixelLight(float3 canonV1, std::shared_ptr<Color> color1, float3 canonV2, std::shared_ptr<Color> color2,
                                   float3 canonV3, std::shared_ptr<Color> color3, const std::vector<PointLight> &pointLights,
                                   DirectionalLight directional, float4x4 world2view, const float3 &worldPos1,
                                   const float3 &worldPos2,
                                   const float3 &worldPos3, const float3 &normal1, const float3 &normal2, const float3 &normal3);
};

#endif // PIXELBUFFER_H
