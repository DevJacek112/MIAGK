//
// Created by Jacek on 19.04.2025.
//

#ifndef TORUS_H
#define TORUS_H
#include "Mesh.h"


class Torus : public Mesh {
    public:
    Torus(float3 position, float R, float r, int majorSegments, int minorSegments);
};



#endif //TORUS_H
