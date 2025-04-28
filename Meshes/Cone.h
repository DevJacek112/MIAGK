#ifndef CONE_H
#define CONE_H

#include "Mesh.h"

class Cone : public Mesh {
public:
    Cone(float3 position, float size, int segments);
};

#endif // CONE_H
