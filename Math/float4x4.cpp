//
// Created by Jacek on 11.04.2025.
//

#include "float4x4.h"

#include <stdexcept>

#include "float3.h"

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

float4 float4x4::operator*(const float4& vec) const {
    return float4(
        (*this)[0][0] * vec.x + (*this)[0][1] * vec.y + (*this)[0][2] * vec.z + (*this)[0][3] * vec.w,
        (*this)[1][0] * vec.x + (*this)[1][1] * vec.y + (*this)[1][2] * vec.z + (*this)[1][3] * vec.w,
        (*this)[2][0] * vec.x + (*this)[2][1] * vec.y + (*this)[2][2] * vec.z + (*this)[2][3] * vec.w,
        (*this)[3][0] * vec.x + (*this)[3][1] * vec.y + (*this)[3][2] * vec.z + (*this)[3][3] * vec.w
    );
}

float4x4 float4x4::Inverse() const {
    float4x4 inv;
    const float* m = reinterpret_cast<const float*>(this); // assumes row-major order

    float invOut[16];

    invOut[0] = m[5]  * m[10] * m[15] -
                m[5]  * m[11] * m[14] -
                m[9]  * m[6]  * m[15] +
                m[9]  * m[7]  * m[14] +
                m[13] * m[6]  * m[11] -
                m[13] * m[7]  * m[10];

    invOut[4] = -m[4]  * m[10] * m[15] +
                 m[4]  * m[11] * m[14] +
                 m[8]  * m[6]  * m[15] -
                 m[8]  * m[7]  * m[14] -
                 m[12] * m[6]  * m[11] +
                 m[12] * m[7]  * m[10];

    invOut[8] = m[4]  * m[9] * m[15] -
                m[4]  * m[11] * m[13] -
                m[8]  * m[5] * m[15] +
                m[8]  * m[7] * m[13] +
                m[12] * m[5] * m[11] -
                m[12] * m[7] * m[9];

    invOut[12] = -m[4]  * m[9] * m[14] +
                  m[4]  * m[10] * m[13] +
                  m[8]  * m[5] * m[14] -
                  m[8]  * m[6] * m[13] -
                  m[12] * m[5] * m[10] +
                  m[12] * m[6] * m[9];

    invOut[1] = -m[1]  * m[10] * m[15] +
                 m[1]  * m[11] * m[14] +
                 m[9]  * m[2] * m[15] -
                 m[9]  * m[3] * m[14] -
                 m[13] * m[2] * m[11] +
                 m[13] * m[3] * m[10];

    invOut[5] = m[0]  * m[10] * m[15] -
                m[0]  * m[11] * m[14] -
                m[8]  * m[2] * m[15] +
                m[8]  * m[3] * m[14] +
                m[12] * m[2] * m[11] -
                m[12] * m[3] * m[10];

    invOut[9] = -m[0]  * m[9] * m[15] +
                 m[0]  * m[11] * m[13] +
                 m[8]  * m[1] * m[15] -
                 m[8]  * m[3] * m[13] -
                 m[12] * m[1] * m[11] +
                 m[12] * m[3] * m[9];

    invOut[13] = m[0]  * m[9] * m[14] -
                 m[0]  * m[10] * m[13] -
                 m[8]  * m[1] * m[14] +
                 m[8]  * m[2] * m[13] +
                 m[12] * m[1] * m[10] -
                 m[12] * m[2] * m[9];

    invOut[2] = m[1]  * m[6] * m[15] -
                m[1]  * m[7] * m[14] -
                m[5]  * m[2] * m[15] +
                m[5]  * m[3] * m[14] +
                m[13] * m[2] * m[7] -
                m[13] * m[3] * m[6];

    invOut[6] = -m[0]  * m[6] * m[15] +
                 m[0]  * m[7] * m[14] +
                 m[4]  * m[2] * m[15] -
                 m[4]  * m[3] * m[14] -
                 m[12] * m[2] * m[7] +
                 m[12] * m[3] * m[6];

    invOut[10] = m[0]  * m[5] * m[15] -
                 m[0]  * m[7] * m[13] -
                 m[4]  * m[1] * m[15] +
                 m[4]  * m[3] * m[13] +
                 m[12] * m[1] * m[7] -
                 m[12] * m[3] * m[5];

    invOut[14] = -m[0]  * m[5] * m[14] +
                  m[0]  * m[6] * m[13] +
                  m[4]  * m[1] * m[14] -
                  m[4]  * m[2] * m[13] -
                  m[12] * m[1] * m[6] +
                  m[12] * m[2] * m[5];

    invOut[3] = -m[1] * m[6] * m[11] +
                 m[1] * m[7] * m[10] +
                 m[5] * m[2] * m[11] -
                 m[5] * m[3] * m[10] -
                 m[9] * m[2] * m[7] +
                 m[9] * m[3] * m[6];

    invOut[7] = m[0] * m[6] * m[11] -
                m[0] * m[7] * m[10] -
                m[4] * m[2] * m[11] +
                m[4] * m[3] * m[10] +
                m[8] * m[2] * m[7] -
                m[8] * m[3] * m[6];

    invOut[11] = -m[0] * m[5] * m[11] +
                  m[0] * m[7] * m[9] +
                  m[4] * m[1] * m[11] -
                  m[4] * m[3] * m[9] -
                  m[8] * m[1] * m[7] +
                  m[8] * m[3] * m[5];

    invOut[15] = m[0] * m[5] * m[10] -
                 m[0] * m[6] * m[9] -
                 m[4] * m[1] * m[10] +
                 m[4] * m[2] * m[9] +
                 m[8] * m[1] * m[6] -
                 m[8] * m[2] * m[5];

    float det = m[0] * invOut[0] + m[1] * invOut[4] + m[2] * invOut[8] + m[3] * invOut[12];

    if (det == 0)
        return float4x4(); // Zwróć jednostkową lub zgłoś błąd

    det = 1.0f / det;

    for (int i = 0; i < 16; i++)
        reinterpret_cast<float*>(&inv)[i] = invOut[i] * det;

    return inv;
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

