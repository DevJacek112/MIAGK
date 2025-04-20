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

    auto pixelBuffer = std::make_shared<PixelBuffer>(1000, 1000);
    pixelBuffer->SetAllPixelsColor(Color::Black());

    Camera camera;
    camera.setLookat(float3(0,0,0), float3(0,0,-1), float3(0,1,0));
    camera.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    camera.SetPixelBuffer(pixelBuffer);
    std::shared_ptr<Cylinder> cone1 = std::make_shared<Cylinder>(float3(-2.1,1.5,-2), 1, 8);
    std::shared_ptr<Cube> cube = std::make_shared<Cube>(1, float3(0,0,-2));
    std::shared_ptr<Cone> cone = std::make_shared<Cone>(float3(2.1,-1.5,-2), 1, 8);

    PointLight light(float3 (-4.2,0.2,-1));

    camera._pointLights.push_back(light);
    camera._meshes.push_back(cone1);
    camera._meshes.push_back(cube);
    camera._meshes.push_back(cone);
    camera.RenderMeshes();

    TGAWriter::SaveToTGA("test.tga", pixelBuffer);

    return 0;
}





