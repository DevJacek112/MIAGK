//
// Created by Jacek on 11.04.2025.
//

#ifndef FLOAT4_H
#define FLOAT4_H

class float4x4;

class float4 {
public:
    union {
        struct {
            float x, y, z, w;
        };
        struct {
            float r, g, b, a;
        };
        float data[4];
    };

    float4() : x(0), y(0), z(0), w(1) {}
    float4(float x, float y, float z, float w);

    float4 &operator*(float4x4);

    float &operator[](int i);

    const float &operator[](int i) const;

    float4 Dot(float4 v);

    float DotProduct(float4 v) const;
};



#endif //FLOAT4_H
