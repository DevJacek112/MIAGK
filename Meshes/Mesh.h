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

struct Index {
    int v1, v2, v3;
};

enum LightningMode {
    NONE,
    VERTICES,
    PIXELS
};

class Mesh {
public:
    std::vector<Vertex> _vertices;
    std::vector<Index> _indices;
    std::shared_ptr<VertexProcessor> _vertexProcessor;

    float _size;
    float3 _centerPosition;
    int textureNumber;
    bool wannaLight = true;

    void GenerateVertexColors();

    LightningMode lightningMode = VERTICES;
};


#endif //MESH_H
