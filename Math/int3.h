#ifndef INT3_H
#define INT3_H

#define M_PI 3.14159265358979323846
#include <cmath>
#include <iostream>
#include <ostream>

class int3 {
public:
    union {
        struct {
            int x, y, z;
        };
        struct {
            int r, g, b;
        };
        int data[3];
    };

    int3() : x(0), y(0), z(0) {}
    int3(int x, int y, int z);

    int operator[](int i) const;

    int3& operator=(const int3& other);

    int3 operator-() const;

    int3 operator+(const int3& v) const;
    int3& operator+=(const int3& v);

    int3 operator-(const int3& v) const;
    int3& operator-=(const int3& v);

    int3 operator*(int f) const;
    int3& operator*=(int f);

    int3 operator/(int f) const;
    int3& operator/=(int f);

    void AddInPlace(int3 v);
    int3 Add(int3 v) const;

    void SubInPlace(int3 v);
    int3 Sub(int3 v) const;

    void MagInPlace(int f);
    int3 Mag(int f) const;

    void DivInPlace(int f);
    int3 Div(int f) const;

    int Length();

    const int epsilon = 0.0001f;
    void Normalize();

    int3 GetNormalized() const;

    int3 Dot(int3 v);
    int DotProduct(int3 v) const;

    int3 Cross(int3 v);

    bool Equals(int3 v);

    int FindAngleRad(int3 v);
    int FindAngleDeg(int3 v);

    int3 Reflect(const int3 &I, const int3 &N);
};



#endif //INT3_H
