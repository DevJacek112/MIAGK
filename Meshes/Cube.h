//
// Created by Jacek on 19.04.2025.
//

#ifndef CUBE_H
#define CUBE_H
#include "Mesh.h"

class Cube : public Mesh {
public:
    Cube(float3 position, float size, float4x4 view2project, float4x4 world2view, const float4x4 &object2world);
};



#endif //CUBE_H
