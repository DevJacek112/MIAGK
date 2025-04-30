//
// Created by Jacek on 19.04.2025.
//
#include <vector>

#include "../Triangle.h"
#include "../Color.h"
#include "../Math/float3.h"
#include "../Math/float4x4.h"

#ifndef MESH_H
#define MESH_H




class Mesh {
public:
    std::vector<float3> _vertices;
    std::vector<float3> _normals;
    std::vector<std::shared_ptr<Color>> _vertexColors;
    std::vector<Triangle> _triangles;

    float _size;
    float3 _centerPosition;
    int textureNumber;
    bool wannaLight = true;

    void GenerateVertexColors();
};


#endif //MESH_H
