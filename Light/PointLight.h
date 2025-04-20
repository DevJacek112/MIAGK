//
// Created by Jacek on 20.04.2025.
//

#include "../Math/float3.h"
#include "../Color.h"
#include "../VertexProcessor.h"

#ifndef POINTLIGHT_H
#define POINTLIGHT_H



class PointLight {
public:
    float3 position;
    float3 ambient;
    float3 diffuse;
    float3 specular;


    PointLight(const float3 &position);

    std::shared_ptr<Color> calculatePhongLighting(const float4x4 &world2view, const float3 &worldPos,
                                                  const float3 &worldNormal, std::shared_ptr<Color> baseColor,
                                                  float shininess, float kd, float ks, float ka);
};



#endif //POINTLIGHT_H
