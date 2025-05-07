//
// Created by Jacek on 20.03.2025.
//

#include <iostream>
#include <limits>

#include "pixelbuffer.h"
#include "Light/Light.h"
#include "Meshes/Cube.h"
#include "Meshes/Mesh.h"

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
    int textureNumber,
    float3 normal1, float3 normal2, float3 normal3,
    std::shared_ptr<Mesh> mesh,
    float3 pos1, float3 pos2, float3 pos3
) {

    /*std::cout << color1->_r << " " << color1->_g << " " << color1->_b << std::endl;
    std::cout << color2->_r << " " << color2->_g << " " << color2->_b << std::endl;
    std::cout << color3->_r << " " << color3->_g << " " << color3->_b << std::endl;*/

    float3 v1 = float3((canonV1.x + 1) * _width * 0.5f,
                       (canonV1.y + 1) * _height * 0.5f,
                       canonV1.z);

    float3 v2 = float3((canonV2.x + 1) * _width * 0.5f,
                       (canonV2.y + 1) * _height * 0.5f,
                       canonV2.z);

    float3 v3 = float3((canonV3.x + 1) * _width * 0.5f,
                       (canonV3.y + 1) * _height * 0.5f,
                       canonV3.z);

    /*float area = (v2.x - v1.x) * (v3.y - v1.y) - (v2.y - v1.y) * (v3.x - v1.x);
    if (area > 0) {
        std::swap(v2, v3);
        std::swap(color2, color3);
    }*/

    float minX = std::max(0.0f, std::min({v1.x, v2.x, v3.x}));
    float maxX = std::min((float)_width - 1, std::max({v1.x, v2.x, v3.x}));
    float minY = std::max(0.0f, std::min({v1.y, v2.y, v3.y}));
    float maxY = std::min((float)_height - 1, std::max({v1.y, v2.y, v3.y}));

    int dy12 = v1.y - v2.y, dy23 = v2.y - v3.y, dy31 = v3.y - v1.y;
    int dx12 = v1.x - v2.x, dx23 = v2.x - v3.x, dx31 = v3.x - v1.x;

    bool tl1 = dy12 < 0 || (dy12 == 0 && dx12 > 0);
    bool tl2 = dy23 < 0 || (dy23 == 0 && dx23 > 0);
    bool tl3 = dy31 < 0 || (dy31 == 0 && dx31 > 0);

    for (int y = minY; y < maxY; y++) {
        for (int x = minX; x < maxX; x++) {

            bool edge1 = ((v1.x - v2.x) * (y - v1.y) - (v1.y - v2.y) * (x - v1.x)) > (tl1 ? -1 : 0);
            bool edge2 = ((v2.x - v3.x) * (y - v2.y) - (v2.y - v3.y) * (x - v2.x)) > (tl2 ? -1 : 0);
            bool edge3 = ((v3.x - v1.x) * (y - v3.y) - (v3.y - v1.y) * (x - v3.x)) > (tl3 ? -1 : 0);

            if (edge1 && edge2 && edge3) {
                int r, g, b;
                float3 baricentricCoords = GetBaricentricTriangleCoords(v1.x, v1.y, v2.x, v2.y, v3.x, v3.y, x, y);
                if (mesh->lightningMode == PIXELS) {

                    // Współczynniki barycentryczne względem v3
                    float v3x = v3.x, v3y = v3.y;
                    float denom = dy23 * (-dx31) + (-dx23) * (-dy31);

                    float k1 = ((dy23 * (x - v3x)) + (-dx23) * (y - v3y)) / denom;
                    float k2 = ((dy31 * (x - v3x)) + (-dx31) * (y - v3y)) / denom;
                    float k3 = 1.0f - k1 - k2;

                    // Interpolacja normalnych
                    float3 interpolatedNormal = normal1 * k1 + normal2 * k2 + normal3 * k3;
                    interpolatedNormal.Normalize();

                    if (mesh->isCube) {
                        float u = baricentricCoords.x * uv1.x + baricentricCoords.y * uv2.x + baricentricCoords.z * uv3.x;
                        float v = baricentricCoords.x * uv1.y + baricentricCoords.y * uv2.y + baricentricCoords.z * uv3.y;

                        Color texColor = SampleTexture(textureNumber, u, v);

                        r = texColor._r;
                        g = texColor._g;
                        b = texColor._b;
                    }else {

                        /*float3 interpolatedNormal = normal1 * k1 + normal2 * k2 + normal3 * k3;
                        interpolatedNormal.Normalize();*/

                        float4 w1_float4 = float4((mesh->_vertexProcessor->_obj2world * float4(pos1.x, pos1.y, pos1.z, 1.0f)));
                        float3 w1_float3 = float3(w1_float4.x, w1_float4.y, w1_float4.z);

                        float4 w2_float4 = float4((mesh->_vertexProcessor->_obj2world * float4(pos2.x, pos2.y, pos2.z, 1.0f)));
                        float3 w2_float3 = float3(w2_float4.x, w2_float4.y, w2_float4.z);

                        float4 w3_float4 = float4((mesh->_vertexProcessor->_obj2world * float4(pos3.x, pos3.y, pos3.z, 1.0f)));
                        float3 w3_float3 = float3(w3_float4.x, w3_float4.y, w3_float4.z);

                        float3 interpolatedWorldPos = w1_float3 * k1 + w2_float3 * k2 + w3_float3 * k3;
                        float3 direction = interpolatedWorldPos;
                        direction.Normalize();
                        Color texColor = SampleCubeTexture(direction, textureNumber);

                        r = texColor._r;
                        g = texColor._g;
                        b = texColor._b;
                    }
                    // Interpolacja pozycji w świecie
                    float4 w1_float4 = float4((mesh->_vertexProcessor->_obj2world * float4(pos1.x, pos1.y, pos1.z, 1.0f)));
                    float3 w1_float3 = float3(w1_float4.x, w1_float4.y, w1_float4.z);

                    float4 w2_float4 = float4((mesh->_vertexProcessor->_obj2world * float4(pos2.x, pos2.y, pos2.z, 1.0f)));
                    float3 w2_float3 = float3(w2_float4.x, w2_float4.y, w2_float4.z);

                    float4 w3_float4 = float4((mesh->_vertexProcessor->_obj2world * float4(pos3.x, pos3.y, pos3.z, 1.0f)));
                    float3 w3_float3 = float3(w3_float4.x, w3_float4.y, w3_float4.z);

                    float3 interpolatedWorldPos = w1_float3 * k1 + w2_float3 * k2 + w3_float3 * k3;

                    std::vector<std::shared_ptr<Light>> lights = mesh->_vertexProcessor->lights;
                    float3 lighting = float3(0, 0, 0);

                    for (const auto& light : lights) {
                        lighting = lighting + light->calculate(*mesh->_vertexProcessor, interpolatedWorldPos, interpolatedNormal);
                    }

                    float lightIntensity = (lighting.x + lighting.y + lighting.z) / 3.0f;

                    r = std::clamp(int(r * lightIntensity), 0, 255);
                    g = std::clamp(int(g * lightIntensity), 0, 255);
                    b = std::clamp(int(b * lightIntensity), 0, 255);
                }
                else if (mesh->lightningMode == VERTICES) {
                    std::shared_ptr<Color> finalColor = InterpolateColor(color1, color2, color3, baricentricCoords);
                    r = finalColor->_r;
                    g = finalColor->_g;
                    b = finalColor->_b;
                }else if (mesh->lightningMode == NONE) {

                    float v3x = v3.x, v3y = v3.y;
                    float denom = dy23 * (-dx31) + (-dx23) * (-dy31);

                    float k1 = ((dy23 * (x - v3x)) + (-dx23) * (y - v3y)) / denom;
                    float k2 = ((dy31 * (x - v3x)) + (-dx31) * (y - v3y)) / denom;
                    float k3 = 1.0f - k1 - k2;
                    if (mesh->isCube) {
                        float u = baricentricCoords.x * uv1.x + baricentricCoords.y * uv2.x + baricentricCoords.z * uv3.x;
                        float v = baricentricCoords.x * uv1.y + baricentricCoords.y * uv2.y + baricentricCoords.z * uv3.y;

                        Color texColor = SampleTexture(textureNumber, u, v);

                        r = texColor._r;
                        g = texColor._g;
                        b = texColor._b;
                    }else {

                        /*float3 interpolatedNormal = normal1 * k1 + normal2 * k2 + normal3 * k3;
                        interpolatedNormal.Normalize();*/

                        float4 w1_float4 = float4((mesh->_vertexProcessor->_obj2world * float4(pos1.x, pos1.y, pos1.z, 1.0f)));
                        float3 w1_float3 = float3(w1_float4.x, w1_float4.y, w1_float4.z);

                        float4 w2_float4 = float4((mesh->_vertexProcessor->_obj2world * float4(pos2.x, pos2.y, pos2.z, 1.0f)));
                        float3 w2_float3 = float3(w2_float4.x, w2_float4.y, w2_float4.z);

                        float4 w3_float4 = float4((mesh->_vertexProcessor->_obj2world * float4(pos3.x, pos3.y, pos3.z, 1.0f)));
                        float3 w3_float3 = float3(w3_float4.x, w3_float4.y, w3_float4.z);

                        float3 interpolatedWorldPos = w1_float3 * k1 + w2_float3 * k2 + w3_float3 * k3;
                        float3 direction = interpolatedWorldPos;
                        direction.Normalize();
                        Color texColor = SampleCubeTexture(direction, textureNumber);

                        r = texColor._r;
                        g = texColor._g;
                        b = texColor._b;

                        r = std::clamp(int(r), 0, 255);
                        g = std::clamp(int(g), 0, 255);
                        b = std::clamp(int(b), 0, 255);
                    }
                }

                float depth = baricentricCoords.x * v1.z + baricentricCoords.y * v2.z + baricentricCoords.z * v3.z;

                if (depth > GetPixelDepth(x, y)) {
                    SetPixelColor(x, y, std::make_shared<Color>(r, g, b, 255));
                    SetPixelDepth(x, y, depth);
                }
            }
        }
    }
}

Color PixelBuffer::SampleCubeTexture(const float3& dir, int numberOfTexture) {
    float absX = fabs(dir.x);
    float absY = fabs(dir.y);
    float absZ = fabs(dir.z);

    int face;
    float u, v;

    if (absX >= absY && absX >= absZ) {
        // X face
        face = dir.x > 0 ? 0 : 1;
        u = dir.z / absX * 0.5f + 0.5f;
        v = dir.y / absX * 0.5f + 0.5f;
    } else if (absY >= absX && absY >= absZ) {
        // Y face
        face = dir.y > 0 ? 2 : 3;
        u = dir.x / absY * 0.5f + 0.5f;
        v = dir.z / absY * 0.5f + 0.5f;
    } else {
        // Z face
        face = dir.z > 0 ? 4 : 5;
        u = dir.x / absZ * 0.5f + 0.5f;
        v = dir.y / absZ * 0.5f + 0.5f;
    }
    return SampleTexture(numberOfTexture, u, v);
}


