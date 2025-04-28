#include "Cube.h"

Cube::Cube(float size, float3 center) {
    _size = size;
    _centerPosition = center;

    float h = size / 2.0f;

    _vertices = {
        float3(-h, -h, -h) + center, // 0
        float3( h, -h, -h) + center, // 1
        float3( h,  h, -h) + center, // 2
        float3(-h,  h, -h) + center, // 3
        float3(-h, -h,  h) + center, // 4
        float3( h, -h,  h) + center, // 5
        float3( h,  h,  h) + center, // 6
        float3(-h,  h,  h) + center  // 7
    };

    _triangles = {
        Triangle(4, 6, 5),
        Triangle(4, 7, 6),

        Triangle(0, 4, 7),
        Triangle(0, 7, 3),

        Triangle(1, 2, 6),
        Triangle(1, 6, 5),

        Triangle(3, 7, 6),
        Triangle(3, 6, 2),

        Triangle(0, 1, 5),
        Triangle(0, 5, 4),

        Triangle(0, 2, 1),
        Triangle(0, 3, 2)
    };
}
