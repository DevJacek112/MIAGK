//
// Created by Jacek on 19.04.2025.
//

#include "Torus.h"

Torus::Torus(float3 position, float R, float r, int majorSegments, int minorSegments) {
    if (majorSegments < 3) majorSegments = 3;
    if (minorSegments < 3) minorSegments = 3;

    for (int i = 0; i < majorSegments; ++i) {
        float angleMajor1 = (2 * M_PI * i) / majorSegments;
        float angleMajor2 = (2 * M_PI * (i + 1)) / majorSegments;

        for (int j = 0; j < minorSegments; ++j) {
            float angleMinor1 = (2 * M_PI * j) / minorSegments;
            float angleMinor2 = (2 * M_PI * (j + 1)) / minorSegments;
            
            float x1 = (R + r * cos(angleMinor1)) * cos(angleMajor1);
            float y1 = (R + r * cos(angleMinor1)) * sin(angleMajor1);
            float z1 = r * sin(angleMinor1);

            float x2 = (R + r * cos(angleMinor2)) * cos(angleMajor1);
            float y2 = (R + r * cos(angleMinor2)) * sin(angleMajor1);
            float z2 = r * sin(angleMinor2);

            float x3 = (R + r * cos(angleMinor2)) * cos(angleMajor2);
            float y3 = (R + r * cos(angleMinor2)) * sin(angleMajor2);
            float z3 = r * sin(angleMinor2);

            float x4 = (R + r * cos(angleMinor1)) * cos(angleMajor2);
            float y4 = (R + r * cos(angleMinor1)) * sin(angleMajor2);
            float z4 = r * sin(angleMinor1);

            _triangles.emplace_back(float3(x1, y1, z1) + position,
                                   float3(x2, y2, z2) + position,
                                   float3(x4, y4, z4) + position,
                                   Color::Red(), Color::Red(), Color::Red());

            _triangles.emplace_back(float3(x2, y2, z2) + position,
                                   float3(x3, y3, z3) + position,
                                   float3(x4, y4, z4) + position,
                                   Color::Blue(), Color::Blue(), Color::Blue());
        }
    }
}
