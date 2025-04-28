//
// Created by Jacek on 19.04.2025.
//

#ifndef CUBE_H
#define CUBE_H
#include "Mesh.h"

class Cube : public Mesh {
public:
    Cube(float size, float3 center = float3(0, 0, 0));
};



#endif //CUBE_H
