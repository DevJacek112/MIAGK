//
// Created by Jacek on 19.04.2025.
//

#ifndef CYLINDER_H
#define CYLINDER_H
#include "Mesh.h"


class Cylinder : public Mesh {
    public:
    Cylinder(float3 position, float size, int segments);
};



#endif //CYLINDER_H
