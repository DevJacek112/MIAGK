#ifndef VECTOR3_H
#define VECTOR3_H

#define M_PI 3.14159265358979323846
#include <cmath>
#include <iostream>
#include <ostream>

class float3 {
public:
    union {
        struct {
            float x, y, z;
        };
        struct {
            float r, g, b;
        };
        float data[3];
    };

    float3() : x(0), y(0), z(0) {}
    float3(float x, float y, float z);

    float operator[](int i) const;

    float3& operator=(const float3& other);

    float3 operator-() const;

    float3 operator+(const float3& v) const;
    float3& operator+=(const float3& v);

    float3 operator-(const float3& v) const;
    float3& operator-=(const float3& v);



    float3 operator/(float f) const;
    float3& operator/=(float f);

    void AddInPlace(float3 v);
    float3 Add(float3 v) const;

    void SubInPlace(float3 v);
    float3 Sub(float3 v) const;

    void MagInPlace(float f);
    float3 Mag(float f) const;

    void DivInPlace(float f);
    float3 Div(float f) const;

    float Length();

    const float epsilon = 0.0001f;
    void Normalize();

    float3 GetNormalized() const;

    float3 Dot(float3 v);
    float DotProduct(float3 v) const;

    float3 Cross(float3 v);

    bool Equals(float3 v);

    float FindAngleRad(float3 v);
    float FindAngleDeg(float3 v);

    float3 Reflect(const float3 &I, const float3 &N);

    float3 saturate(const float3 &v);
};

inline float3 operator*(float scalar, const float3& vec) {
    return float3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

inline float3 operator*(const float3& vec, float scalar) {
    return float3(vec.x * scalar, vec.y * scalar, vec.z * scalar);
}

inline float3 operator/(const float3& vec, float scalar) {
    return float3(vec.x / scalar, vec.y / scalar, vec.z / scalar);
}

inline float3& operator*=(float3& a, const float3& b) {
    a.x *= b.x;
    a.y *= b.y;
    a.z *= b.z;
    return a;
}

inline float3 operator*(const float3& a, const float3& b) {
    return float3(a.x * b.x, a.y * b.y, a.z * b.z);
}

#endif //VECTOR3_H
