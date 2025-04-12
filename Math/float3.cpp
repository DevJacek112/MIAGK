#include "Float3.h"

float3::float3(float x, float y, float z) : x(x), y(y), z(z)
{

}

float float3::operator[](int i) const {
    return data[i];
}

float3& float3::operator=(const float3& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

// negacja
float3 float3::operator-() const {
    return float3(-x, -y, -z);
}

// Przeciążenie operatora + (dodawanie wektorów)
float3 float3::operator+(const float3& v)   const{
    return this->Add(v);
}

// Przeciążenie operatora += (dodawanie w miejscu)
float3& float3::operator+=(const float3& v){
    this->AddInPlace(v);
    return *this;
}

// Przeciążenie operatora - (odejmowanie wektorów)
float3 float3::operator-(const float3& v) const {
    return this->Sub(v);
}

// Przeciążenie operatora -= (odejmowanie w miejscu)
float3& float3::operator-=(const float3& v) {
    this->SubInPlace(v);
    return *this;
}

// Przeciążenie operatora * (skalowanie przez skalar)
float3 float3::operator*(float f)  const{
    return this->Mag(f);
}

// Przeciążenie operatora *= (skalowanie w miejscu)
float3& float3::operator*=(float f) {
    this->MagInPlace(f);
    return *this;
}

// Przeciążenie operatora / (dzielenie przez skalar)
float3 float3::operator/(float f)  const{
    return this->Div(f);
}

// Przeciążenie operatora /= (dzielenie w miejscu)
float3& float3::operator/=(float f) {
    this->DivInPlace(f);
    return *this;
}

void float3::AddInPlace(float3 v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

float3 float3::Add(float3 v)  const{
    float3 result = *this;

    result.x += v.x;
    result.y += v.y;
    result.z += v.z;

    return result;
}

void float3::SubInPlace(float3 v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

float3 float3::Sub(float3 v) const {
    float3 result = *this;
    result.x -= v.x;
    result.y -= v.y;
    result.z -= v.z;
    return result;
}

void float3::MagInPlace(float f) {
    x *= f;
    y *= f;
    z *= f;
}

float3 float3::Mag(float f)  const{
    float3 result = *this;
    result.x *= f;
    result.y *= f;
    result.z *= f;
    return result;
}

void float3::DivInPlace(float f) {
    if (f != 0) {
        x /= f;
        y /= f;
        z /= f;
    } else {
        std::cout << "Division by zero detected!" << std::endl;
    }
}

float3 float3::Div(float f)  const{
    float3 result = *this;
    if (f != 0) {
        result.x /= f;
        result.y /= f;
        result.z /= f;
    } else {
        std::cout << "Division by zero detected!" << std::endl;
    }
    return result;
}

float float3::Length() {
    return (float)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void float3::Normalize() {
    float len=sqrt (x * x + y * y + z * z);
    if ( len > epsilon ) {
        x /= len;
        y /= len;
        z /= len;
    }
    else x=y=z =0.0f;
}

float3 float3::GetNormalized() const{
    float3 result = *this;
    result.Normalize();
    return result;
}

float3 float3::Dot(float3 v) {
    float3 result = float3(0, 0, 0);
    result.x = x * v.x;
    result.y = y * v.y;
    result.z = z * v.z;
    return result;
}

float float3::DotProduct(float3 v) const {
    float3 result = float3(0, 0, 0);
    result.x = x * v.x;
    result.y = y * v.y;
    result.z = z * v.z;
    return result.x + result.y + result.z;
}

float3 float3::Cross(float3 v) {
    return float3(y * v.z - z * v.y,
                   z * v.x - x * v.z,
                   x * v.y - y * v.x);
}


bool float3::Equals(float3 v) {
    if (x == v.x && y == v.y && z == v.z) {
        return true;
    }
    else {
        return false;
    }
}

float float3::FindAngleRad(float3 v) {
    return acos(DotProduct(v) / (Length() * v.Length()));
}

float float3::FindAngleDeg(float3 v) {
    return FindAngleRad(v) * (180.0f / M_PI);
}

float3 float3::Reflect(const float3& I, const float3& N) {
    float dotProduct = I.DotProduct(N);
    float scale = 2.0f * dotProduct;
    return I - N * scale;
}

float3 float3::saturate(const float3& v) {
    return float3(
        std::max(0.0f, std::min(1.0f, v.x)),
        std::max(0.0f, std::min(1.0f, v.y)),
        std::max(0.0f, std::min(1.0f, v.z))
    );
}


