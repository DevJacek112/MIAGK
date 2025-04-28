#include "Cylinder.h"

Cylinder::Cylinder(float3 position, float size, int segments) {
    if (segments < 3) segments = 3;

    float radius = size * 0.5f;
    float height = size;

    float3 topCenter = float3(position.x, position.y + height * 0.5f, position.z);
    float3 bottomCenter = float3(position.x, position.y - height * 0.5f, position.z);

    int baseIndex = 0;

    _vertices.push_back(topCenter);    // indeks 0
    _vertices.push_back(bottomCenter); // indeks 1

    for (int i = 0; i < segments; ++i) {
        float angle = (2 * M_PI * i) / segments;
        float x = position.x + cos(angle) * radius;
        float z = position.z + sin(angle) * radius;

        _vertices.push_back(float3(x, topCenter.y, z));    // top point
        _vertices.push_back(float3(x, bottomCenter.y, z)); // bottom point
    }

    for (int i = 0; i < segments; ++i) {
        int top1 = 2 + i * 2;
        int bottom1 = 2 + i * 2 + 1;
        int top2 = 2 + ((i + 1) % segments) * 2;
        int bottom2 = 2 + ((i + 1) % segments) * 2 + 1;

        _triangles.push_back(Triangle(top1, top2, bottom2));
        _triangles.push_back(Triangle(top1, bottom2, bottom1));
    }

    for (int i = 0; i < segments; ++i) {
        int top = 2 + i * 2;
        int nextTop = 2 + ((i + 1) % segments) * 2;

        _triangles.push_back(Triangle(0, nextTop, top));
    }

    for (int i = 0; i < segments; ++i) {
        int bottom = 2 + i * 2 + 1;
        int nextBottom = 2 + ((i + 1) % segments) * 2 + 1;

        _triangles.push_back(Triangle(1, bottom, nextBottom));
    }
}
