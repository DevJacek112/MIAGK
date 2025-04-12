//
// Created by Jacek on 11.04.2025.
//

#include "float4.h"

#include "float4x4.h"

float4::float4(float x, float y, float z, float w) : x(x), y(y), z(z), w(w)
{

}

float4& float4::operator*(float4x4 mat) {
    this->x = mat[0][0] * this->x + mat[0][1] * this->y + mat[0][2] * this->z + mat[0][3] * this->w;
    this->y = mat[1][0] * this->x + mat[1][1] * this->y + mat[1][2] * this->z + mat[1][3] * this->w;
    this->z = mat[2][0] * this->x + mat[2][1] * this->y + mat[2][2] * this->z + mat[2][3] * this->w;
    this->w = mat[3][0] * this->x + mat[3][1] * this->y + mat[3][2] * this->z + mat[3][3] * this->w;

    return *this;
}

float& float4::operator[](int i) {
    return data[i];
}

const float& float4::operator[](int i) const {
    return data[i];
}

float4 float4::Dot(float4 v) {
    float4 result = float4();
    result.x = x * v.x;
    result.y = y * v.y;
    result.z = z * v.z;
    result.w = w * v.w;
    return result;
}

float float4::DotProduct(float4 v) const {
    float4 result = float4();
    result.x = x * v.x;
    result.y = y * v.y;
    result.z = z * v.z;
    result.w = w * v.w;
    return result.x + result.y + result.z + result.w;
}