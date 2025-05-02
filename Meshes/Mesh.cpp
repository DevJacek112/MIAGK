#include "Mesh.h"
#include "../Light/Light.h"

/*void Mesh::GenerateNormals() {
    _normals.resize(_vertices.size(), float3(0, 0, 0));

    for (auto& tri : _triangles) {
        float3 v0 = _vertices[tri[0]];
        float3 v1 = _vertices[tri[1]];
        float3 v2 = _vertices[tri[2]];

        _normals[tri[0]] = VertexProcessor::transformNormal(v0, world2view);
        _normals[tri[1]] = VertexProcessor::transformNormal(v1, world2view);
        _normals[tri[2]] = VertexProcessor::transformNormal(v2, world2view);
    }

    for (auto& n : _normals) {
        n.Normalize();
    }
}*/

void Mesh::GenerateVertexColors() {
    for (auto& v: _vertices) {
        v.normal = _vertexProcessor->transformNormal(v.normal);
        v.normal.Normalize();

        /*std::cout << v.normal.x << ", " << v.normal.y << ", " << v.normal.z << std::endl;*/

        float4 worldPos4 = _vertexProcessor->_obj2world * float4(v.position.x, v.position.y, v.position.z, 1.0f);
        float3 worldPos = float3(worldPos4.x, worldPos4.y, worldPos4.z);

        float4 worldNormal4 = _vertexProcessor->_obj2world * float4(v.normal.x, v.normal.y, v.normal.z, 0.0f);
        float3 worldNormal = float3(worldNormal4.x, worldNormal4.y, worldNormal4.z);
        worldNormal.Normalize();



        float3 lighting = float3(0.5, 0.5, 0.5);

        for (const auto& light : _vertexProcessor->getLights()) {
            lighting = lighting + light->calculate(*_vertexProcessor, worldPos, worldNormal);
        }

        float lightIntensity = (lighting.x + lighting.y + lighting.z) / 3.0f;

        float r = v.vertexColor->_r, g = v.vertexColor->_g, b = v.vertexColor->_b;

        r = std::clamp(int(r * lightIntensity), 0, 255);
        g = std::clamp(int(g * lightIntensity), 0, 255);
        b = std::clamp(int(b * lightIntensity), 0, 255);

        v.vertexColor = std::make_shared<Color>(r, g, b, 1.0f);
    }
}


