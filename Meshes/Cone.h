#ifndef CONE_H
#define CONE_H

#include "Mesh.h"

class Cone : public Mesh {
public:
    Cone(float3 position, float size, int segments, float4x4 view2project, float4x4 world2view, float4x4 object2world);
};

#endif // CONE_H
