//
// Created by Jacek on 11.04.2025.
//

#include "float4x4.h"

#include <stdexcept>

float4x4::float4x4(float4 a, float4 b, float4 c, float4 d): columns{} {
    columns[0] = a;
    columns[1] = b;
    columns[2] = c;
    columns[3] = d;
}

float4x4::float4x4() {
    columns[0] = float4(0.0f,0.0f,0.0f,0.0f);
    columns[1] = float4(0.0f,0.0f,0.0f,0.0f);
    columns[2] = float4(0.0f,0.0f,0.0f,0.0f);
    columns[3] = float4(0.0f,0.0f,0.0f,0.0f);
}

float4& float4x4::operator[](int i) {
    return columns[i];
}

const float4& float4x4::operator[](int i) const {
    return columns[i];
}

float4x4 float4x4::operator*(const float4x4 &v) const {
    float4x4 result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result[row][col] = 0.0f;
            for (int k = 0; k < 4; ++k) {
                result[row][col] += (*this)[row][k] * v[k][col];
            }
        }
    }

    return result;
}

float4x4 float4x4::operator*(float v) const {
    float4x4 result;

    for (int row = 0; row < 4; ++row) {
        for (int col = 0; col < 4; ++col) {
            result[row][col] = (*this)[row][col] * v;
        }
    }

    return result;
}

float4 float4x4::operator*(const float4& vec) {
    return float4(
        (*this)[0].x * vec.x + (*this)[1].x * vec.y + (*this)[2].x * vec.z + (*this)[3].x * vec.w,
        (*this)[0].y * vec.x + (*this)[1].y * vec.y + (*this)[2].y * vec.z + (*this)[3].y * vec.w,
        (*this)[0].z * vec.x + (*this)[1].z * vec.y + (*this)[2].z * vec.z + (*this)[3].z * vec.w,
        (*this)[0].w * vec.x + (*this)[1].w * vec.y + (*this)[2].w * vec.z + (*this)[3].w * vec.w
    );
}


float4x4 float4x4::Transpose() {
    float4x4 result;

    result[0][0] = (*this)[0][0];
    result[0][1] = (*this)[1][0];
    result[0][2] = (*this)[2][0];
    result[0][3] = (*this)[3][0];

    result[1][0] = (*this)[0][1];
    result[1][1] = (*this)[1][1];
    result[1][2] = (*this)[2][1];
    result[1][3] = (*this)[3][1];

    result[2][0] = (*this)[0][2];
    result[2][1] = (*this)[1][2];
    result[2][2] = (*this)[2][2];
    result[2][3] = (*this)[3][2];

    result[3][0] = (*this)[0][3];
    result[3][1] = (*this)[1][3];
    result[3][2] = (*this)[2][3];
    result[3][3] = (*this)[3][3];

    return result;
}
