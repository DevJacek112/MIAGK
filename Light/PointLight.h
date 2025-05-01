//
// Created by Jacek on 1.05.2025.
//

#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include "Light.h"


class PointLight : public Light {
public:
    PointLight(const float3 &position, const float3 &ambient, const float3 &diffuse, const float3 &specular,
               float shininess);
    float3 calculate(VertexProcessor& vp, const float3& pointPosition, const float3& normal) override;

};



#endif //POINTLIGHT_H
