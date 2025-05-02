//
// Created by Jacek on 1.05.2025.
//

#include "PointLight.h"

PointLight::PointLight(const float3 &position, const float3 &ambient, const float3 &diffuse, const float3 &specular,
                       float shininess) : Light(position, ambient, diffuse, specular, shininess) {

}

float3 PointLight::calculate(VertexProcessor& vp, const float3& pointPosition, const float3& normal)
{
    // 1. N - normal do przestrzeni widoku
    float4 N4 = (vp._world2view * float4(normal.x, normal.y, normal.z, 0.0f));
    float3 N = float3(N4.x, N4.y, N4.z);
    N.Normalize();


    /*for (int i = 0; i < 3; i++) {
        std::cout << normal.x << ", "<< normal.y << ", "<< normal.z;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;*/

    /*for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << vp._world2view[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;*/

    // 2. V - wektor do kamery (przeciwny do przekształconej pozycji wierzchołka)
    float4 posView4 = (vp._world2view * float4(pointPosition.x, pointPosition.y, pointPosition.z, 1.0f));
    float3 posView = float3(posView4.x, posView4.y, posView4.z);
    float3 V = {-posView.x, -posView.y, -posView.z};
    V.Normalize();

    // 3. L - kierunek od światła do fragmentu (pozycja fragmentu - pozycja światła)
    float4 lightPosView4 = (vp._world2view * float4(position.x, position.y, position.z, 1.0f));
    float3 lightPosView = float3(lightPosView4.x, lightPosView4.y, lightPosView4.z);
    float3 L = (lightPosView - pointPosition);
    L.Normalize();

    // 4. R - odbity wektor
    float3 R = (2.0f * N.DotProduct(L) * N - L);
    R.Normalize();

    // 5. Diffuse - obliczanie współczynnika diffuse (oświetlenie zależne od kąta)
    float diff = std::max(N.DotProduct(L), 0.0f);

    // 6. Specular - obliczanie współczynnika specular (współczynnik lustrzany)
    float spec = 0.0f;
    if (diff > 0.0f) {
        spec = pow(std::max(R.DotProduct(V), 0.0f), shininess);
    }


    // 7. Zwróć ostateczny kolor z uwzględnieniem zasięgu światła
    return (ambient + diffuse * diff + specular * spec);
}