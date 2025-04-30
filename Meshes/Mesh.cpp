#include "Mesh.h"

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
    _vertexColors.resize(_vertices.size());

    auto baseColor = std::make_shared<Color>(255, 255, 255, 255);

    for (int i = 0; i < _vertices.size(); ++i) {
        auto finalColor = std::make_shared<Color>(255, 255, 255, 0);

        finalColor->_r = std::min(255, finalColor->_r);
        finalColor->_g = std::min(255, finalColor->_g);
        finalColor->_b = std::min(255, finalColor->_b);

        _vertexColors[i] = finalColor;
        //std::cout << _vertexColors[i]->_r << ", " << _vertexColors[i]->_g << ", " << _vertexColors[i]->_b << std::endl;
    }
}


