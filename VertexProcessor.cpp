//
// Created by Jacek on 20.04.2025.
//

#include "VertexProcessor.h"

float4 VertexProcessor::LocalToWorld(float4 pos, float4x4 obj2world) {
    return obj2world * pos;
}

float4 VertexProcessor::WorldToView(float4 pos, float4x4 world2view) {
    return world2view * pos;
}

float3 VertexProcessor::WorldToView(float3 pos, float4x4 world2view) {
    float4 res = world2view * float4(pos.x, pos.y, pos.z, 1.0f);
    return float3(res.x, res.y, res.z);
}

float3 VertexProcessor::TransformNormal(float3 normal, float4x4 obj2world, float4x4 world2view) {
    float4 nWorld = obj2world * float4(normal.x, normal.y, normal.z, 0.0f);
    float4 nView = world2view * nWorld;
    float3 result = float3(nView.x, nView.y, nView.z);
    result.Normalize();
    return result;
}

float3 VertexProcessor::WorldToViewNormal(float3 normal, float4x4 world2view) {
    float4 nView = world2view * float4(normal.x, normal.y, normal.z, 0.0f);
    float3 result = float3(nView.x, nView.y, nView.z);
    result.Normalize();
    return result;
}

float3 VertexProcessor::WorldToViewDirection(float3 dir, float4x4 world2view) {
    float4 dView = world2view * float4(dir.x, dir.y, dir.z, 0.0f);
    return float3(dView.x, dView.y, dView.z).GetNormalized();
}

float3 VertexProcessor::transformNormal(const float3& normal, float4x4 world2view) {
    float4 n = float4(normal.x, normal.y, normal.z, 0.0f);
    float4 transformed = world2view * n;
    float3 result = float3(transformed.x, transformed.y, transformed.z);
    result.Normalize();
    return result;
}
