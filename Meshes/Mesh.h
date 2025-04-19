//
// Created by Jacek on 19.04.2025.
//
#include <vector>

#include "../Triangle.h"
#include "../Color.h"

#ifndef MESH_H
#define MESH_H



class Mesh {
    public:
    std::vector<Triangle> _triangles;
    float _size;
    float3 _centerPosition;
};



#endif //MESH_H
