#include "Cylinder.h"

Cylinder::Cylinder(float3 position, float size, int slices, float4x4 view2project, float4x4 world2view, float4x4 object2world)
{
    _vertexProcessor = std::make_shared<VertexProcessor>();
    _vertexProcessor->_view2proj = view2project;
    _vertexProcessor->_world2view = world2view;
    _vertexProcessor->_obj2world = object2world;

    if (slices < 3) slices = 3;
    int stacks = 1; // możesz też dodać to jako parametr

    float radius = size * 0.5f;
    float height = size;

    float angleStep = 2.0f * M_PI / slices;
    float heightStep = height / stacks;

    // === Side Vertices ===
    for (int j = 0; j <= stacks; ++j) {
        float z = -height * 0.5f + j * heightStep;

        for (int i = 0; i < slices; ++i) {
            float angle = i * angleStep;
            float x = cos(angle) * radius;
            float y = sin(angle) * radius;
            float3 normal = float3(x, y, 0).GetNormalized();

            float3 pos = float3(x, y, z) + position;
            float3 color = float3(1, 1, 1); // albo losuj jeśli chcesz

            _vertices.push_back({ pos, normal, std::make_shared<Color>(color.r * 255, color.g * 255, color.b * 255, 255) });
        }
    }

    // === Side Indices ===
    for (int j = 0; j < stacks; ++j) {
        for (int i = 0; i < slices; ++i) {
            int curr = j * slices + i;
            int next = j * slices + (i + 1) % slices;
            int upper = (j + 1) * slices + i;
            int upperNext = (j + 1) * slices + (i + 1) % slices;

            _indices.push_back({ curr, next, upper });
            _indices.push_back({ next, upperNext, upper });
        }
    }

    // === Bottom Cap ===
    int bottomCenterIndex = _vertices.size();
    _vertices.push_back({ position - float3(0, 0, height * 0.5f), float3(0, 0, -1), std::make_shared<Color>(255, 255, 255, 255) });

    int bottomStart = _vertices.size();
    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        float3 pos = float3(x, y, -height * 0.5f) + position;
        _vertices.push_back({ pos, float3(0, 0, -1), std::make_shared<Color>(255, 255, 255, 255) });
    }

    for (int i = 0; i < slices; ++i) {
        int curr = bottomStart + i;
        int next = bottomStart + (i + 1) % slices;
        _indices.push_back({ next, curr, bottomCenterIndex });
    }

    // === Top Cap ===
    int topCenterIndex = _vertices.size();
    _vertices.push_back({ position + float3(0, 0, height * 0.5f), float3(0, 0, 1), std::make_shared<Color>(255, 255, 255, 255) });

    int topStart = _vertices.size();
    for (int i = 0; i < slices; ++i) {
        float angle = i * angleStep;
        float x = cos(angle) * radius;
        float y = sin(angle) * radius;

        float3 pos = float3(x, y, height * 0.5f) + position;
        _vertices.push_back({ pos, float3(0, 0, 1), std::make_shared<Color>(255, 255, 255, 255) });
    }

    for (int i = 0; i < slices; ++i) {
        int curr = topStart + i;
        int next = topStart + (i + 1) % slices;
        _indices.push_back({ topCenterIndex, curr, next });
    }

    GenerateVertexColors();
}

