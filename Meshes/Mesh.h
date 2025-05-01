//
// Created by Jacek on 19.04.2025.
//
#include <vector>

#include "VertexProcessor.h"
#include "../Triangle.h"
#include "../Color.h"
#include "../Math/float3.h"
#include "../Math/float4x4.h"

#ifndef MESH_H
#define MESH_H

struct Vertex {
    float3 position;
    float3 normal;
    std::shared_ptr<Color> vertexColor;
};

class Mesh {
public:
    std::vector<Vertex> _vertices;
    std::vector<Triangle> _triangles;
    std::shared_ptr<VertexProcessor> _vertexProcessor;

    float _size;
    float3 _centerPosition;
    int textureNumber;
    bool wannaLight = true;

    void GenerateVertexColors();
};


#endif //MESH_H
