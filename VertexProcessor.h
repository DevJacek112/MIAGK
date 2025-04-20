//
// Created by Jacek on 20.04.2025.
//

#ifndef VERTEXPROCESSOR_H
#define VERTEXPROCESSOR_H
#include "Math/Float3.h"
#include "Math/float4.h"
#include "Math/float4x4.h"

class VertexProcessor {
public:
    static float4 LocalToWorld(float4 pos, float4x4 obj2world) {
        return obj2world * pos;
    }

    static float4 WorldToView(float4 pos, float4x4 world2view) {
        return world2view * pos;
    }

    static float3 WorldToView(float3 pos, float4x4 world2view) {
        float4 res = world2view * float4(pos.x, pos.y, pos.z, 1.0f);
        return float3(res.x, res.y, res.z);
    }

    static float3 TransformNormal(float3 normal, float4x4 obj2world, float4x4 world2view) {
        float4 nWorld = obj2world * float4(normal.x, normal.y, normal.z, 0.0f);
        float4 nView = world2view * nWorld;
        float3 result = float3(nView.x, nView.y, nView.z);
        result.Normalize();
        return result;
    }

    static float3 WorldToViewNormal(float3 normal, float4x4 world2view) {
        float4 nView = world2view * float4(normal.x, normal.y, normal.z, 0.0f);
        float3 result = float3(nView.x, nView.y, nView.z);
        result.Normalize();
        return result;
    }

    static float3 WorldToViewDirection(float3 dir, float4x4 world2view) {
        float4 dView = world2view * float4(dir.x, dir.y, dir.z, 0.0f);
        return float3(dView.x, dView.y, dView.z).GetNormalized();
    }
};



#endif //VERTEXPROCESSOR_H
