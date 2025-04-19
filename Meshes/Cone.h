//
// Created by Jacek on 19.04.2025.
//

#ifndef CONE_H
#define CONE_H
#include "Mesh.h"


class Cone : public Mesh {
public:
    Cone(float3 position, float size, int segments);
};



#endif //CONE_H
