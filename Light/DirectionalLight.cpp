//
// Created by Jacek on 20.04.2025.
//

#include "DirectionalLight.h"
#include <algorithm>

DirectionalLight::DirectionalLight(const float3 &direction)
    : direction(direction.GetNormalized()),
      ambient(0.9f, 0.9f, 0.9f),
      diffuse(0.6f, 0.6f, 0.6f),
      specular(.0f, .0f, .0f)
{
}

std::shared_ptr<Color> DirectionalLight::calculatePhongLighting(
    const float4x4 &world2view,
    const float3 &worldPos,
    const float3 &worldNormal,
    const std::shared_ptr<Color> baseColor,
    float shininess,
    float kd, float ks, float ka
) {
    float3 posView = VertexProcessor::WorldToView(worldPos, world2view);
    float3 normalView = VertexProcessor::WorldToViewNormal(worldNormal, world2view);
    float3 lightDirView = VertexProcessor::WorldToViewDirection(-direction, world2view);

    float3 N = normalView.GetNormalized();
    float3 L = lightDirView.GetNormalized();
    float3 V = -posView.GetNormalized();
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