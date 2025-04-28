#include "Cone.h"

Cone::Cone(float3 position, float size, int segments) {
    if (segments < 3) segments = 3;

    float radius = size * 0.5f;
    float height = size;

    float3 apex = float3(position.x, position.y + height, position.z);
    float3 center = position;

    _vertices.push_back(apex);
    _vertices.push_back(center);

    for (int i = 0; i < segments; ++i) {
        float angle = (2 * M_PI * i) / segments;
        float x = center.x + cos(angle) * radius;
        float z = center.z + sin(angle) * radius;
        _vertices.push_back(float3(x, center.y, z));
    }

    for (int i = 0; i < segments; ++i) {
        int v1 = 2 + i;
        int v2 = 2 + (i + 1) % segments;

        _triangles.push_back(Triangle(0, v1, v2));
    }

    for (int i = 0; i < segments; ++i) {
        int v1 = 2 + i;
        int v2 = 2 + (i + 1) % segments;

        _triangles.push_back(Triangle(1, v2, v1));
    }
}
