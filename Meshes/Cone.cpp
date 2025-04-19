//
// Created by Jacek on 19.04.2025.
//

#include "Cone.h"

Cone::Cone(float3 position, float size, int segments) {

    if (segments < 3) segments = 3;

    float radius = size * 0.5f;
    float height = size;

    float3 apex = float3(position.x, position.y + height, position.z);
    float3 center = position;

    std::vector<float3> basePoints;

    for (int i = 0; i < segments; ++i) {
        float angle = (2 * M_PI * i) / segments;
        float x = center.x + cos(angle) * radius;
        float z = center.z + sin(angle) * radius;
        float3 point = float3(x, center.y, z);
        basePoints.push_back(point);
    }

    for (int i = 0; i < segments; ++i) {
        float3 v1 = basePoints[i];
        float3 v2 = basePoints[(i + 1) % segments];
        _triangles.emplace_back(apex, v1, v2, Color::Blue(), Color::Blue(), Color::Blue());
    }

    for (int i = 0; i < segments; ++i) {
        float3 v1 = basePoints[i];
        float3 v2 = basePoints[(i + 1) % segments];
        _triangles.emplace_back(center, v2, v1, Color::Red(), Color::Red(), Color::Red());
    }
}
