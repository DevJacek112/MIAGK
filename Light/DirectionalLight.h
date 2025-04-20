//
// Created by Jacek on 20.04.2025.
//

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "../Math/float3.h"
#include "../Color.h"
#include "../VertexProcessor.h"

class DirectionalLight {
public:
    float3 direction;
    float3 ambient;
    float3 diffuse;
    float3 specular;

    DirectionalLight(const float3 &direction);

    std::shared_ptr<Color> calculatePhongLighting(const float4x4 &world2view, const float3 &worldPos,
                                                  const float3 &worldNormal, std::shared_ptr<Color> baseColor,
                                                  float shininess, float kd, float ks, float ka);
};



#endif //DIRECTIONALLIGHT_H
