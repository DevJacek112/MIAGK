//
// Created by Jacek on 12.04.2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <math.h>

#include "PixelBuffer.h"
#include "Triangle.h"
#include "Light/DirectionalLight.h"
#include "Light/PointLight.h"
#include "Math/float4x4.h"
#include "Meshes/Mesh.h"


class Camera {
    public:
    float4x4 _view2Proj;
    float4x4 _world2View;
    float4x4 _obj2world;
    std::shared_ptr<PixelBuffer> _pixelBuffer;
    std::vector<std::shared_ptr<Mesh>> _meshes;
    std::vector<PointLight> _pointLights;
    DirectionalLight _directionalLight = DirectionalLight(float3(1,0,0));;

    Camera();

    void setLookat(float3 eye, float3 center, float3 up);

    void setPerspective(float fovy, float aspect, float near, float far);

    void RenderTriangle(Triangle& triangle);

    void SetPixelBuffer(std::shared_ptr<PixelBuffer> pixelBuffer);

    void RenderMeshes();

};



#endif //CAMERA_H
