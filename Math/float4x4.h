//
// Created by Jacek on 11.04.2025.
//

#ifndef FLOAT4X4_H
#define FLOAT4X4_H
#include "float4.h"


class float4x4 {
    public:
    float4 columns[4];

    float4x4(float4 a, float4 b, float4 c, float4 d);

    float4x4();

    float4 &operator[](int i);

    const float4 &operator[](int i) const;

    float4x4 operator*(const float4x4 &v) const;

    float4x4 operator*(float v) const;

    float4 operator*(const float4 &vec);

    float4x4 Transpose();
};



#endif //FLOAT4X4_H
