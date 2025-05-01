//
// Created by Jacek on 1.05.2025.
//

#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H
#include "Light.h"


class DirectionalLight : public Light {
public:
    float3 direction;

    DirectionalLight(const float3 &position, const float3 &ambient, const float3 &diffuse, const float3 &specular,
                     float shininess, const float3 &direction);

    float3 calculate(VertexProcessor& vp, const float3& pointPosition, const float3& normal) override;
};



#endif //DIRECTIONALLIGHT_H
