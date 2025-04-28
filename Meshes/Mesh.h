//
// Created by Jacek on 19.04.2025.
//
#include <vector>

#include "../Triangle.h"
#include "../Color.h"
#include "../Light/DirectionalLight.h"
#include "../Light/PointLight.h"

#ifndef MESH_H
#define MESH_H




class Mesh {
public:
    std::vector<float3> _vertices;
    std::vector<float3> _normals;
    std::vector<std::shared_ptr<Color>> _vertexColors;
    std::vector<Triangle> _triangles;
    float4x4 world2view;

    float _size;
    float3 _centerPosition;

    void GenerateNormals();
    void GenerateVertexColors(const std::vector<PointLight> &pointLights, DirectionalLight &directionalLight);
};


#endif //MESH_H
