//
// Created by Jacek on 21.03.2025.
//

#ifndef VECTOR3_H
#define VECTOR3_H

class Vector3 {
public:
    Vector3() : x(0), y(0), z(0) {}
    Vector3(float x, float y, float z);

    float x, y, z;

    void AddInPlace(Vector3 v);
    Vector3 Add(Vector3 v) const;

    void SubInPlace(Vector3 v);
    Vector3 Sub(Vector3 v) const;

    void MagInPlace(float f);
    Vector3 Mag(float f) const;

    void DivInPlace(float f);
    Vector3 Div(float f) const;

    Vector3 operator+(const Vector3& v) const;
    Vector3& operator+=(const Vector3& v);

    Vector3 operator-(const Vector3& v) const;
    Vector3& operator-=(const Vector3& v);

    Vector3 operator*(float f) const;
    Vector3& operator*=(float f);

    Vector3 operator/(float f) const;
    Vector3& operator/=(float f);

    float Length();

    void Normalize();
    Vector3 GetNormalized() const;

    Vector3 Dot(Vector3 v);
    float DotProduct(Vector3 v) const;

    Vector3 Cross(Vector3 v);

    bool Equals(Vector3 v);

    float FindAngleRad(Vector3 v);
    float FindAngleDeg(Vector3 v);
};

#endif //VECTOR3_H
