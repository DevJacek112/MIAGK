//
// Created by Jacek on 21.03.2025.
//

#include "Vector3.h"
#define M_PI 3.14159265358979323846
#include <cmath>
#include <iostream>
#include <ostream>

Vector3::Vector3(float x, float y, float z) : x(x), y(y), z(z)
{

}

void Vector3::AddInPlace(Vector3 v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

Vector3 Vector3::Add(Vector3 v)  const{
    Vector3 result = *this;

    result.x += v.x;
    result.y += v.y;
    result.z += v.z;

    return result;
}

void Vector3::SubInPlace(Vector3 v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

Vector3 Vector3::Sub(Vector3 v) const {
    Vector3 result = *this;
    result.x -= v.x;
    result.y -= v.y;
    result.z -= v.z;
    return result;
}

void Vector3::MagInPlace(float f) {
    x *= f;
    y *= f;
    z *= f;
}

Vector3 Vector3::Mag(float f)  const{
    Vector3 result = *this;
    result.x *= f;
    result.y *= f;
    result.z *= f;
    return result;
}

void Vector3::DivInPlace(float f) {
    if (f != 0) {
        x /= f;
        y /= f;
        z /= f;
    } else {
        std::cout << "Division by zero detected!" << std::endl;
    }
}

Vector3 Vector3::Div(float f)  const{
    Vector3 result = *this;
    if (f != 0) {
        result.x /= f;
        result.y /= f;
        result.z /= f;
    } else {
        std::cout << "Division by zero detected!" << std::endl;
    }
    return result;
}

// Przeciążenie operatora + (dodawanie wektorów)
Vector3 Vector3::operator+(const Vector3& v)   const{
    return this->Add(v);
}

// Przeciążenie operatora += (dodawanie w miejscu)
Vector3& Vector3::operator+=(const Vector3& v){
    this->AddInPlace(v);
    return *this;
}

// Przeciążenie operatora - (odejmowanie wektorów)
Vector3 Vector3::operator-(const Vector3& v) const {
    return this->Sub(v);
}

// Przeciążenie operatora -= (odejmowanie w miejscu)
Vector3& Vector3::operator-=(const Vector3& v) {
    this->SubInPlace(v);
    return *this;
}

// Przeciążenie operatora * (skalowanie przez skalar)
Vector3 Vector3::operator*(float f)  const{
    return this->Mag(f);
}

// Przeciążenie operatora *= (skalowanie w miejscu)
Vector3& Vector3::operator*=(float f) {
    this->MagInPlace(f);
    return *this;
}

// Przeciążenie operatora / (dzielenie przez skalar)
Vector3 Vector3::operator/(float f)  const{
    return this->Div(f);
}

// Przeciążenie operatora /= (dzielenie w miejscu)
Vector3& Vector3::operator/=(float f) {
    this->DivInPlace(f);
    return *this;
}

float Vector3::Length() {
    return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Vector3::Normalize() {
    float n = Length();
    if (n != 0) {
        DivInPlace(n);
    }
    else {
        std::cout << "Division by zero detected!" << std::endl;
    }
}

Vector3 Vector3::GetNormalized() const{
    Vector3 result = *this;
    result.Normalize();
    return result;
}

Vector3 Vector3::Dot(Vector3 v) {
    Vector3 result = Vector3(0, 0, 0);
    result.x = x * v.x;
    result.y = y * v.y;
    result.z = z * v.z;
    return result;
}

float Vector3::DotProduct(Vector3 v) const {
    Vector3 result = Vector3(0, 0, 0);
    result.x = x * v.x;
    result.y = y * v.y;
    result.z = z * v.z;
    return result.x + result.y + result.z;
}

Vector3 Vector3::Cross(Vector3 v) {
    return Vector3(y * v.z - z * v.y,
                   z * v.x - x * v.z,
                   x * v.y - y * v.x);
}


bool Vector3::Equals(Vector3 v) {
    if (x == v.x && y == v.y && z == v.z) {
        return true;
    }
    else {
        return false;
    }
}

float Vector3::FindAngleRad(Vector3 v) {
    return acos(DotProduct(v) / (Length() * v.Length()));
}

float Vector3::FindAngleDeg(Vector3 v) {
    return FindAngleRad(v) * (180.0f / M_PI);
}
