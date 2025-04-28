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
    static float4 LocalToWorld(float4 pos, float4x4 obj2world);

    static float4 WorldToView(float4 pos, float4x4 world2view);

    static float3 WorldToView(float3 pos, float4x4 world2view);

    static float3 TransformNormal(float3 normal, float4x4 obj2world, float4x4 world2view);

    static float3 WorldToViewNormal(float3 normal, float4x4 world2view);

    static float3 WorldToViewDirection(float3 dir, float4x4 world2view);

    static float3 transformNormal(const float3 &normal, float4x4 world2view);
};



#endif //VERTEXPROCESSOR_H
