//
// Created by Jacek on 19.04.2025.
//

#include "Cube.h"

Cube::Cube(float size, float3 center) {
    _size = size;
    _centerPosition = center;

    float h = size / 2.0f;

    float3 v0 = {-h, -h, -h};
    v0 += center;
    float3 v1 = { h, -h, -h};
    v1 += center;
    float3 v2 = { h,  h, -h};
    v2 += center;
    float3 v3 = {-h,  h, -h};
    v3 += center;



    float3 v4 = {-h, -h,  h};
    v4 += center;
    float3 v5 = { h, -h,  h};
    v5 += center;
    float3 v6 = { h,  h,  h};
    v6 += center;
    float3 v7 = {-h,  h,  h};
    v7 += center;

    // front face
    /*_triangles.emplace_back(Triangle(v4, v6, v5, Color::Green(), Color::Green(), Color::Green()));
    _triangles.emplace_back(Triangle(v4, v7, v6, Color::Green(), Color::Green(), Color::Green()));*/

    // left face
    _triangles.emplace_back(Triangle(v0, v4, v7, Color::Blue(), Color::Blue(), Color::Blue()));
    _triangles.emplace_back(Triangle(v0, v7, v3, Color::Blue(), Color::Blue(), Color::Blue()));

    // right face
    _triangles.emplace_back(Triangle(v1, v2, v6, Color::Green(), Color::Green(), Color::Green()));
    _triangles.emplace_back(Triangle(v1, v6, v5, Color::Green(), Color::Green(), Color::Green()));

    // top face
    _triangles.emplace_back(Triangle(v3, v7, v6, Color::White(), Color::White(), Color::White()));
    _triangles.emplace_back(Triangle(v3, v6, v2, Color::White(), Color::White(), Color::White()));

    // bottom face
    _triangles.emplace_back(Triangle(v0, v1, v5, Color::White(), Color::White(), Color::White()));
    _triangles.emplace_back(Triangle(v0, v5, v4, Color::White(), Color::White(), Color::White()));

    // back face
    _triangles.emplace_back(Triangle(v0, v2, v1, Color::Red(), Color::Red(), Color::Red()));
    _triangles.emplace_back(Triangle(v0, v3, v2, Color::Red(), Color::Red(), Color::Red()));
}
