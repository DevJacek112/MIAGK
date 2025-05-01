//
// Created by Jacek on 1.05.2025.
//

#include "VertexProcessor.h"

void VertexProcessor::addLight(std::shared_ptr<Light> light)
{
    lights.push_back(light);
}

const std::vector<std::shared_ptr<Light>> VertexProcessor::getLights() const
{
    return lights;
}

float3 VertexProcessor::transformNormal(const float3& normal) {
    float4 n = float4(normal.x, normal.y, normal.z, 0.0f);
    float4 transformed = _world2view * n;
    float3 result = float3(transformed.x, transformed.y, transformed.z);
    result.Normalize();
    return result;
}