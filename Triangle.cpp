//
// Created by Jacek on 12.04.2025.
//

#include "Triangle.h"

Triangle::Triangle(const float3 &v1, const float3 &v2, const float3 &v3, const std::shared_ptr<Color> &v1_color,
                   const std::shared_ptr<Color> &v2_color, const std::shared_ptr<Color> &v3_color): _v1(v1),
    _v2(v2),
    _v3(v3),
    _v1Color(v1_color),
    _v2Color(v2_color),
    _v3Color(v3_color) {
    _obj2world = float4x4(
        float4(1, 0, 0, 0),
        float4(0, 1, 0, 0),
        float4(0, 0, 1, 0),
        float4(0, 0, 0, 1)
    );
}

void Triangle::Scale(float3 scale) {
    float4x4 m = float4x4(
        float4(scale.x, 0, 0, 0),
        float4(0, scale.y, 0, 0),
        float4(0, 0, scale.z, 0),
        float4(0, 0, 0, 1)
    );
    _obj2world = m * _obj2world;
}

void Triangle::Rotate(float angle, float3 axis) {
    float s = sin(angle * M_PI / 180), c = cos(angle * M_PI / 180);
    axis.Normalize();
    float4x4 m(
        float4(axis.x * axis.x * (1 - c) + c, axis.y * axis.x * (1 - c) + axis.z * s,
               axis.x * axis.z * (1 - c) - axis.y * s, 0),
        float4(axis.x * axis.y * (1 - c) - axis.z * s, axis.y * axis.y * (1 - c) + c,
               axis.y * axis.z * (1 - c) + axis.x * s, 0),
        float4(axis.x * axis.z * (1 - c) + axis.y * s, axis.y * axis.z * (1 - c) - axis.x * s,
               axis.z * axis.z * (1 - c) + c, 0),
        float4(0, 0, 0, 1));
    _obj2world = m * _obj2world;
}

void Triangle::Translate(float3 translate) {
        float4x4 m = float4x4(
        float4(1, 0, 0, translate.x),
        float4(0, 1, 0, translate.y),
        float4(0, 0, 1, translate.z),
        float4(0, 0, 0, 1)
    );
    _obj2world = m * _obj2world;
}
