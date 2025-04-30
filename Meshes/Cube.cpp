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
        // Front face
        Triangle(0, 1, 2), Triangle(0, 2, 3),
        // Back face
        Triangle(5, 4, 7), Triangle(5, 7, 6),
        // Left face
        Triangle(4, 0, 3), Triangle(4, 3, 7),
        // Right face
        Triangle(1, 5, 6), Triangle(1, 6, 2),
        // Top face
        Triangle(3, 2, 6), Triangle(3, 6, 7),
        // Bottom face
        Triangle(4, 5, 1), Triangle(4, 1, 0)

    };

}
