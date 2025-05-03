#include "Cylinder.h"

Cylinder::Cylinder(float3 position, float size, int segments, float4x4 view2project, float4x4 world2view, float4x4 object2world)
{
    _vertexProcessor = std::make_shared<VertexProcessor>();
    _vertexProcessor->_view2proj = view2project;
    _vertexProcessor->_world2view = world2view;
    _vertexProcessor->_obj2world = object2world;

    _vertices.clear();
    _indices.clear();

    float radius = size / 2;
    float height = size;
    float3 top_center = position + float3(0, height / 2.0f, 0);
    float3 bottom_center = position - float3(0, height / 2.0f, 0);
    std::vector<float3> top_ring;
    std::vector<float3> bottom_ring;

    for (int i = 0; i < segments; i++) {
        float angle = 2 * M_PI * i / segments;
        float x = cos(angle) * radius;
        float z = sin(angle) * radius;
        top_ring.push_back(top_center + float3(x, 0, z));
        bottom_ring.push_back(bottom_center + float3(x, 0, z));
    }

    for (int i = 0; i < segments; i++) {
        float3 p0 = top_ring[i];
        float3 p1 = top_ring[(i+1)%segments];
        float3 p2 = bottom_ring[(i+1)%segments];
        float3 p3 = bottom_ring[i];

        float3 normal = -(p1 - p0).Cross(p3 - p0).GetNormalized();

        int baseIndex = static_cast<int>(_vertices.size());

        _vertices.push_back({ p0, normal, std::make_shared<Color>(255, 255, 0, 0) });
        _vertices.push_back({ p1, normal, std::make_shared<Color>(255, 255, 0, 0) });
        _vertices.push_back({ p2, normal, std::make_shared<Color>(255, 255, 0, 0) });
        _vertices.push_back({ p3, normal, std::make_shared<Color>(255, 255, 0, 0) });

        _indices.push_back({ baseIndex + 0, baseIndex + 2, baseIndex + 1 });
        _indices.push_back({ baseIndex + 0, baseIndex + 3, baseIndex + 2 });

    }


    for (int i = 0; i < segments; i++) {
        float3 p0 = top_center;
        float3 p1 = top_ring[(i+1)%segments];
        float3 p2 = top_ring[i];

        float3 normal = float3(0, -1, 0);

        int baseIndex = static_cast<int>(_vertices.size());

        _vertices.push_back({ p0, normal, std::make_shared<Color>(0, 255, 0, 0) });
        _vertices.push_back({ p1, normal, std::make_shared<Color>(0, 255, 0, 0) });
        _vertices.push_back({ p2, normal, std::make_shared<Color>(0, 255, 0, 0) });

        _indices.push_back({ baseIndex + 0, baseIndex + 2, baseIndex + 1 });

    }

    for (int i = 0; i < segments; i++) {
        float3 p0 = bottom_center;
        float3 p1 = bottom_ring[i];
        float3 p2 = bottom_ring[(i+1)%segments];

        float3 normal = float3(0, 1, 0);

        int baseIndex = static_cast<int>(_vertices.size());

        _vertices.push_back({ p0, normal, std::make_shared<Color>(255, 0, 0, 0) });
        _vertices.push_back({ p1, normal, std::make_shared<Color>(255, 0, 0, 0) });
        _vertices.push_back({ p2, normal, std::make_shared<Color>(255, 0, 0, 0) });

        _indices.push_back({ baseIndex + 0, baseIndex + 2, baseIndex + 1 });

    }

    GenerateVertexColors();
}
