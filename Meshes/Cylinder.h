#ifndef CYLINDER_H
#define CYLINDER_H

#include "Mesh.h"

class Cylinder : public Mesh {
public:
    Cylinder(float3 position, float size, int segments, float4x4 view2project, float4x4 world2view,
             float4x4 object2world);
};

#endif // CYLINDER_H
