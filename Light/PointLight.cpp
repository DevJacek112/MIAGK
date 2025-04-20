//
// Created by Jacek on 20.04.2025.
//

#include "PointLight.h"
#include <iostream>
#include <algorithm>

PointLight::PointLight(const float3 &position)
    : position(position),
      ambient(0.7f, 0.7f, 0.7f),
      diffuse(1.0f, 1.0f, 1.0f),
      specular(1.0f, 1.0f, 1.0f)
{
}

std::shared_ptr<Color> PointLight::calculatePhongLighting(
    const float4x4 &world2view,
    const float3 &worldPos,
    const float3 &worldNormal,
    const std::shared_ptr<Color> baseColor,
    float shininess,
    float kd, float ks, float ka
) {
    float3 N = worldNormal.GetNormalized();
    float3 L = (position - worldPos).GetNormalized();
    float3 V = (-worldPos).GetNormalized(); // zakładamy, że kamera jest w (0,0,0)
    float3 R = R.Reflect(-L, N);

    float dotProductNL = N.DotProduct(L);
    float diffuseIntensity = std::max(dotProductNL, 0.0f);
    float specularIntensity = 0.0f;

    if (diffuseIntensity > 0.0f) {
        float dotProductRV = R.DotProduct(V);
        specularIntensity = std::pow(std::max(dotProductRV, 0.0f), shininess);
    }

    float3 diffuse = kd * diffuseIntensity * this->diffuse;
    float3 specular = ks * specularIntensity * this->specular;
    float3 ambient = ka * this->ambient;

    float3 finalColor = ambient + diffuse + specular;

    float3 baseColorNorm(
        baseColor->_r / 255.0f,
        baseColor->_g / 255.0f,
        baseColor->_b / 255.0f
    );

    finalColor = float3(
        finalColor.x * baseColorNorm.x,
        finalColor.y * baseColorNorm.y,
        finalColor.z * baseColorNorm.z
    );

    int r = static_cast<int>(std::clamp(finalColor.x, 0.0f, 1.0f) * 255.0f);
    int g = static_cast<int>(std::clamp(finalColor.y, 0.0f, 1.0f) * 255.0f);
    int b = static_cast<int>(std::clamp(finalColor.z, 0.0f, 1.0f) * 255.0f);

    return std::make_shared<Color>(r, g, b, 122);
}

