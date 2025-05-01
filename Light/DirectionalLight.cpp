//
// Created by Jacek on 1.05.2025.
//

#include "DirectionalLight.h"

float3 DirectionalLight::calculate(VertexProcessor& vp, const float3& pointPosition, const float3& normal)
{
    // 1. N - normal do przestrzeni widoku
    float4 N4 = (vp._world2view * float4(normal.x, normal.y, normal.z, 0.0f));
    float3 N = float3(N4.x, N4.y, N4.z);
    N.Normalize();

    // 2. V - wektor do kamery (przeciwny do przekształconej pozycji wierzchołka)
    float4 posView4 = (vp._world2view * float4(pointPosition.x, pointPosition.y, pointPosition.z, 1.0f));
    float3 posView = float3(posView4.x, posView4.y, posView4.z);
    float3 V = {-posView.x, -posView.y, -posView.z};
    V.Normalize();

    // 3. L - kierunek światła do przestrzeni widoku
    float4 L4 = (vp._world2view * float4(-direction.x, -direction.y, -direction.z, 0.0f));
    float3 L = float3(L4.x, L4.y, L4.z);
    L.Normalize();

    // 4. R - odbity wektor
    float3 R = (2.0f * N.DotProduct(L) * N - L);
    R.Normalize();

    // 5. Diffuse
    float diff = std::max(N.DotProduct(L), 0.0f);

    // 6. Specular
    float spec = 0.0f;
    if (diff > 0.0f) {
        spec = pow(std::max(R.DotProduct(V), 0.0f), shininess);
    }

    return ambient + diffuse * diff + specular * spec;
}

DirectionalLight::DirectionalLight(const float3 &position, const float3 &ambient, const float3 &diffuse,
                                   const float3 &specular, float shininess, const float3 &direction) :
                                   Light(position,ambient,diffuse,specular,shininess),direction(direction)
{

}