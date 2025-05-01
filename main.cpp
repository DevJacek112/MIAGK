#include <iostream>
#include <memory>

#include "Camera.h"
#include "Color.h"
#include "PixelBuffer.h"
#include "Texture.h"
#include "TGAWriter.h"
#include "Light/DirectionalLight.h"
#include "Math/float4x4.h"
#include "Meshes/Cone.h"
#include "Meshes/Cube.h"
#include "Meshes/Cylinder.h"
#include "Meshes/Torus.h"

int main() {


    auto pixelBuffer = std::make_shared<PixelBuffer>(2000, 2000);
    pixelBuffer->SetAllPixelsColor(Color::Blue());

    Camera camera;

    camera.setLookat(float3(0,0,-1), float3(0,0,0), float3(0,1,0));
    camera.setPerspective(90.0f, 1.0f, 0.1f, 100.0f);
    camera.SetPixelBuffer(pixelBuffer);

    std::shared_ptr<Cube> cube = std::make_shared<Cube>(float3(0,0,-1), 0.5, camera._view2Proj, camera._world2View, camera._obj2world);
    std::shared_ptr<Cube> cube1 = std::make_shared<Cube>(float3(1,0,-1), 0.5, camera._view2Proj, camera._world2View, camera._obj2world);
    std::shared_ptr<Cube> cube2 = std::make_shared<Cube>(float3(-1,0,-1), 0.5, camera._view2Proj, camera._world2View, camera._obj2world);
    std::shared_ptr<Cube> cube3 = std::make_shared<Cube>(float3(0,1,-1), 0.5, camera._view2Proj, camera._world2View, camera._obj2world);
    std::shared_ptr<Cube> cube4 = std::make_shared<Cube>(float3(0,-1,-1), 0.5, camera._view2Proj, camera._world2View, camera._obj2world);
    std::shared_ptr<Cube> cube5 = std::make_shared<Cube>(float3(1,1,-1), 0.5, camera._view2Proj, camera._world2View, camera._obj2world);
    std::shared_ptr<Cube> cube6 = std::make_shared<Cube>(float3(1,-1,-1), 0.5, camera._view2Proj, camera._world2View, camera._obj2world);
    std::shared_ptr<Cube> cube7 = std::make_shared<Cube>(float3(-1,1,-1), 0.5, camera._view2Proj, camera._world2View, camera._obj2world);
    std::shared_ptr<Cube> cube8 = std::make_shared<Cube>(float3(-1,-1,-1), 0.5, camera._view2Proj, camera._world2View, camera._obj2world);

    //LIGHT

    float3 directionalDir(1.0f, 0.0f, 0.0f);
    directionalDir.Normalize();

    std::shared_ptr<DirectionalLight> light = std::make_shared<DirectionalLight>(float3(100.0, 0, 0.0), float3(0.05f, 0.05f, 0.05f),
                                                   float3(1.0f,1.0f,0.5f), float3(0.0f, 0.0f, 1.0f),
                                                   32, directionalDir);

    cube->_vertexProcessor->addLight(light);
    cube1->_vertexProcessor->addLight(light);
    cube2->_vertexProcessor->addLight(light);
    cube3->_vertexProcessor->addLight(light);
    cube4->_vertexProcessor->addLight(light);
    cube5->_vertexProcessor->addLight(light);
    cube6->_vertexProcessor->addLight(light);
    cube7->_vertexProcessor->addLight(light);
    cube8->_vertexProcessor->addLight(light);

    //END OF LIGHT

    cube->GenerateVertexColors();
    cube1->GenerateVertexColors();
    cube2->GenerateVertexColors();
    cube3->GenerateVertexColors();
    cube4->GenerateVertexColors();
    cube5->GenerateVertexColors();
    cube6->GenerateVertexColors();
    cube7->GenerateVertexColors();
    cube8->GenerateVertexColors();

    Texture tex1, tex2;
    tex1.LoadFromTGA("../tex2.tga");
    tex2.LoadFromTGA("../tex3.tga");
    pixelBuffer->tex1 = std::make_shared<Texture>(tex1);
    pixelBuffer->tex2 = std::make_shared<Texture>(tex2);

    cube->textureNumber = 2;
    cube1->textureNumber = 2;
    cube2->textureNumber = 2;
    cube3->textureNumber = 1;
    cube4->textureNumber = 1;
    cube5->textureNumber = 1;
    cube6->textureNumber = 1;
    cube7->textureNumber = 1;
    cube8->textureNumber = 1;

    camera._meshes.push_back(cube);
    camera._meshes.push_back(cube1);
    camera._meshes.push_back(cube2);
    camera._meshes.push_back(cube3);
    camera._meshes.push_back(cube4);
    camera._meshes.push_back(cube5);
    camera._meshes.push_back(cube6);
    camera._meshes.push_back(cube7);
    camera._meshes.push_back(cube8);
    camera.RenderMeshes();

    TGAWriter::SaveToTGA("test.tga", pixelBuffer);

    return 0;
}





