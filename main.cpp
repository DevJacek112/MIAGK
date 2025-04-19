#include <iostream>
#include <memory>

#include "Camera.h"
#include "Color.h"
#include "PixelBuffer.h"
#include "TGAWriter.h"
#include "Math/float4x4.h"
#include "Meshes/Cube.h"

int main() {

    auto pixelBuffer = std::make_shared<PixelBuffer>(500, 500);
    pixelBuffer->SetAllPixelsColor(Color::Black());

    /*triangle.Scale(float3(1,2,1));
    triangle.Rotate(20, float3(0, 1, 0));
    triangle.Translate(float3(2, 0, 0));*/

    Camera camera;
    camera.setLookat(float3(0,0,0), float3(0,0,-1), float3(0,1,0));
    camera.setPerspective(120.0f, 1.0f, 0.1f, 100.0f);
    camera.SetPixelBuffer(pixelBuffer);
    //std::shared_ptr<Cube> cube = std::make_shared<Cube>(2, float3(0,0,0));
    std::shared_ptr<Cube> cube1 = std::make_shared<Cube>(1, float3(2.1,0,-2));
    std::shared_ptr<Cube> cube2 = std::make_shared<Cube>(1, float3(0,0,-2));
    std::shared_ptr<Cube> cube3 = std::make_shared<Cube>(1, float3(-2.1,0,-2));
    //camera._meshes.push_back(cube);
    camera._meshes.push_back(cube1);
    camera._meshes.push_back(cube2);
    camera._meshes.push_back(cube3);
    camera.RenderMeshes();

    TGAWriter::SaveToTGA("test.tga", pixelBuffer);

    return 0;
}





