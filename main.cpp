#include <iostream>
#include <memory>

#include "Camera.h"
#include "Color.h"
#include "PixelBuffer.h"
#include "TGAWriter.h"
#include "Math/float4x4.h"
#include "Meshes/Cone.h"
#include "Meshes/Cube.h"
#include "Meshes/Cylinder.h"
#include "Meshes/Torus.h"

int main() {


    auto pixelBuffer = std::make_shared<PixelBuffer>(2000, 2000);
    pixelBuffer->SetAllPixelsColor(Color::Blue());

    Camera camera;


    camera.setLookat(float3(0,0,1), float3(0,0,0), float3(0,1,0));
    camera.setPerspective(110.0f, 1.0f, 0.1f, 100.0f);
    camera.SetPixelBuffer(pixelBuffer);
    std::shared_ptr<Cylinder> cone1 = std::make_shared<Cylinder>(float3(-1.1,1,-1), 0.5, 8);
    std::shared_ptr<Cube> cube = std::make_shared<Cube>(0.5, float3(0,0,-1));
    std::shared_ptr<Cone> cone = std::make_shared<Cone>(float3(1.1,-1,-1), 0.5, 8);

    cone1->world2view = camera._world2View;
    cube->world2view = camera._world2View;
    cone->world2view = camera._world2View;

    PointLight light(float3(-1,5,-2));

    camera._pointLights.push_back(light);

    cone1->GenerateNormals();
    cube->GenerateNormals();
    cone->GenerateNormals();

    cone1->GenerateVertexColors(camera._pointLights, camera._directionalLight);
    cube->GenerateVertexColors(camera._pointLights, camera._directionalLight);
    cone->GenerateVertexColors(camera._pointLights, camera._directionalLight);

    camera._meshes.push_back(cone1);
    camera._meshes.push_back(cube);
    camera._meshes.push_back(cone);
    camera.RenderMeshes();

    TGAWriter::SaveToTGA("test.tga", pixelBuffer);

    return 0;
}





