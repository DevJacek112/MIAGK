//
// Created by Jacek on 19.04.2025.
//

#include "Cylinder.h"

Cylinder::Cylinder(float3 position, float size, int segments) {
            if (segments < 3) segments = 3;

        float radius = size * 0.5f;
        float height = size;

        float3 topCenter = float3(position.x, position.y + height * 0.5f, position.z);  // środek górnej podstawy
        float3 bottomCenter = float3(position.x, position.y - height * 0.5f, position.z);  // środek dolnej podstawy

        std::vector<float3> topBasePoints;
        std::vector<float3> bottomBasePoints;

        for (int i = 0; i < segments; ++i) {
            float angle = (2 * M_PI * i) / segments;
            float x = position.x + cos(angle) * radius;
            float z = position.z + sin(angle) * radius;

            float3 topPoint = float3(x, topCenter.y, z);
            float3 bottomPoint = float3(x, bottomCenter.y, z);

            topBasePoints.push_back(topPoint);
            bottomBasePoints.push_back(bottomPoint);
        }

        for (int i = 0; i < segments; ++i) {
            float3 v1 = topBasePoints[i];
            float3 v2 = topBasePoints[(i + 1) % segments];
            float3 v3 = bottomBasePoints[(i + 1) % segments];
            float3 v4 = bottomBasePoints[i];

            _triangles.emplace_back(v1, v2, v3, Color::Green(), Color::Green(), Color::Green());  // Pierwszy trójkąt
            _triangles.emplace_back(v1, v3, v4, Color::Green(), Color::Green(), Color::Green());  // Drugi trójkąt
        }

        for (int i = 0; i < segments; ++i) {
            float3 v1 = topBasePoints[i];
            float3 v2 = topBasePoints[(i + 1) % segments];
            _triangles.emplace_back(topCenter, v2, v1, Color::Blue(), Color::Blue(), Color::Blue());  // Trójkąt dla górnej podstawy
        }

        for (int i = 0; i < segments; ++i) {
            float3 v1 = bottomBasePoints[i];
            float3 v2 = bottomBasePoints[(i + 1) % segments];
            _triangles.emplace_back(bottomCenter, v1, v2, Color::Red(), Color::Red(), Color::Red());  // Trójkąt dla dolnej podstawy
        }
}
