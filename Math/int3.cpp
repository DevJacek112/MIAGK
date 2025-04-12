#include "int3.h"

int3::int3(int x, int y, int z) : x(x), y(y), z(z)
{

}

int int3::operator[](int i) const {
    return data[i];
}

int3& int3::operator=(const int3& other) {
    if (this != &other) {
        x = other.x;
        y = other.y;
        z = other.z;
    }
    return *this;
}

// negacja
int3 int3::operator-() const {
    return int3(-x, -y, -z);
}

// Przeciążenie operatora + (dodawanie wektorów)
int3 int3::operator+(const int3& v)   const{
    return this->Add(v);
}

// Przeciążenie operatora += (dodawanie w miejscu)
int3& int3::operator+=(const int3& v){
    this->AddInPlace(v);
    return *this;
}

// Przeciążenie operatora - (odejmowanie wektorów)
int3 int3::operator-(const int3& v) const {
    return this->Sub(v);
}

// Przeciążenie operatora -= (odejmowanie w miejscu)
int3& int3::operator-=(const int3& v) {
    this->SubInPlace(v);
    return *this;
}

// Przeciążenie operatora * (skalowanie przez skalar)
int3 int3::operator*(int f)  const{
    return this->Mag(f);
}

// Przeciążenie operatora *= (skalowanie w miejscu)
int3& int3::operator*=(int f) {
    this->MagInPlace(f);
    return *this;
}

// Przeciążenie operatora / (dzielenie przez skalar)
int3 int3::operator/(int f)  const{
    return this->Div(f);
}

// Przeciążenie operatora /= (dzielenie w miejscu)
int3& int3::operator/=(int f) {
    this->DivInPlace(f);
    return *this;
}

void int3::AddInPlace(int3 v) {
    x += v.x;
    y += v.y;
    z += v.z;
}

int3 int3::Add(int3 v)  const{
    int3 result = *this;

    result.x += v.x;
    result.y += v.y;
    result.z += v.z;

    return result;
}

void int3::SubInPlace(int3 v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
}

int3 int3::Sub(int3 v) const {
    int3 result = *this;
    result.x -= v.x;
    result.y -= v.y;
    result.z -= v.z;
    return result;
}

void int3::MagInPlace(int f) {
    x *= f;
    y *= f;
    z *= f;
}

int3 int3::Mag(int f)  const{
    int3 result = *this;
    result.x *= f;
    result.y *= f;
    result.z *= f;
    return result;
}

void int3::DivInPlace(int f) {
    if (f != 0) {
        x /= f;
        y /= f;
        z /= f;
    } else {
        std::cout << "Division by zero detected!" << std::endl;
    }
}

int3 int3::Div(int f)  const{
    int3 result = *this;
    if (f != 0) {
        result.x /= f;
        result.y /= f;
        result.z /= f;
    } else {
        std::cout << "Division by zero detected!" << std::endl;
    }
    return result;
}

int int3::Length() {
    return (int)sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void int3::Normalize() {
    int len=sqrt (x * x + y * y + z * z);
    if ( len > epsilon ) {
        x /= len;
        y /= len;
        z /= len;
    }
    else x=y=z =0.0f;
}

int3 int3::GetNormalized() const{
    int3 result = *this;
    result.Normalize();
    return result;
}

int3 int3::Dot(int3 v) {
    int3 result = int3(0, 0, 0);
    result.x = x * v.x;
    result.y = y * v.y;
    result.z = z * v.z;
    return result;
}

int int3::DotProduct(int3 v) const {
    int3 result = int3(0, 0, 0);
    result.x = x * v.x;
    result.y = y * v.y;
    result.z = z * v.z;
    return result.x + result.y + result.z;
}

int3 int3::Cross(int3 v) {
    return int3(y * v.z - z * v.y,
                   z * v.x - x * v.z,
                   x * v.y - y * v.x);
}


bool int3::Equals(int3 v) {
    if (x == v.x && y == v.y && z == v.z) {
        return true;
    }
    else {
        return false;
    }
}

int int3::FindAngleRad(int3 v) {
    return acos(DotProduct(v) / (Length() * v.Length()));
}

int int3::FindAngleDeg(int3 v) {
    return FindAngleRad(v) * (180.0f / M_PI);
}

int3 int3::Reflect(const int3& I, const int3& N) {
    float dotProduct = I.DotProduct(N);
    float scale = 2 * dotProduct;
    return I - N * scale;
}
