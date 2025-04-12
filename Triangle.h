//
// Created by Jacek on 12.04.2025.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <memory>

#include "Color.h"
#include "Math/Float3.h"
#include "Math/float4x4.h"


class Triangle {
public:
    float3 _v1, _v2, _v3;
    std::shared_ptr<Color> _v1Color, _v2Color, _v3Color;
    float4x4 _obj2world;

    Triangle(const float3 &v1, const float3 &v2, const float3 &v3, const std::shared_ptr<Color> &v1_color,
        const std::shared_ptr<Color> &v2_color, const std::shared_ptr<Color> &v3_color);

    void Scale(float3 scale);

    void Rotate(float angle, float3 axis);

    void Translate(float3 translate);
};



#endif //TRIANGLE_H
