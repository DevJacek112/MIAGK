#include "Cube.h"

Cube::Cube(float3 position, float size, float4x4 view2project, float4x4 world2view, const float4x4 &object2world) {

    _vertexProcessor = std::make_shared<VertexProcessor>();
    _vertexProcessor->_view2proj = view2project;
    _vertexProcessor->_world2view = world2view;
    _vertexProcessor->_obj2world = object2world;

    _size = size;
    _centerPosition = position;

    float h = size / 2.0f;

    // Wierzchołki sześcianu
    float3 p[8] = {
        float3(-h, -h, -h) + position, // 0
        float3( h, -h, -h) + position, // 1
        float3( h,  h, -h) + position, // 2
        float3(-h,  h, -h) + position, // 3
        float3(-h, -h,  h) + position, // 4
        float3( h, -h,  h) + position, // 5
        float3( h,  h,  h) + position, // 6
        float3(-h,  h,  h) + position  // 7
    };

    // Każda ściana jako 4 wierzchołki z dynamicznie liczonymi normalami
    _vertices = {};

    auto add_face = [&](int i0, int i1, int i2, int i3) {
        float3 edge1 = p[i1] - p[i0];
        float3 edge2 = p[i2] - p[i0];
        float3 normal = edge1.Cross(edge2).GetNormalized();

        int baseIndex = static_cast<int>(_vertices.size());

        _vertices.push_back({ p[i0], normal, std::make_shared<Color>(255,255,0,0) }); // 0
        _vertices.push_back({ p[i1], normal, std::make_shared<Color>(255,255,0,0) }); // 1
        _vertices.push_back({ p[i2], normal, std::make_shared<Color>(255,255,0,0) }); // 2
        _vertices.push_back({ p[i3], normal, std::make_shared<Color>(255,255,0,0) }); // 3

        // Dodaj dwa trójkąty na podstawie czterech wierzchołków (quad -> 2 triangles)
        _indices.push_back({ baseIndex + 0, baseIndex + 1, baseIndex + 2 });
        _indices.push_back({ baseIndex + 0, baseIndex + 2, baseIndex + 3 });
    };


    // Front face (-Z)
    add_face(0, 1, 2, 3);
    // Back face (+Z)
    add_face(5, 4, 7, 6);
    // Left face (-X)
    add_face(4, 0, 3, 7);
    // Right face (+X)
    add_face(1, 5, 6, 2);
    // Top face (+Y)
    add_face(3, 2, 6, 7);
    // Bottom face (-Y)
    add_face(4, 5, 1, 0);

    GenerateVertexColors();
}

