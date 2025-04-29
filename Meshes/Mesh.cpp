#include "Mesh.h"

void Mesh::GenerateNormals() {
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
}

void Mesh::GenerateVertexColors(const std::vector<PointLight> &pointLights, DirectionalLight &directionalLight) {
    _vertexColors.resize(_vertices.size());

    float kd = 1.0f;
    float ks = 0.5f;
    float ka = 0.2f;
    float shininess = 16.0f;
    auto baseColor = std::make_shared<Color>(255, 255, 255, 255);

    for (int i = 0; i < _vertices.size(); ++i) {
        auto finalColor = std::make_shared<Color>(0, 0, 0, 0);

        for (const auto& light : pointLights) {
            auto color = light.calculatePhongLighting(
                _vertices[i],
                _normals[i],
                baseColor,
                shininess,
                kd, ks, ka
            );

            finalColor->_r = std::min(255, finalColor->_r + color->_r);
            finalColor->_g = std::min(255, finalColor->_g + color->_g);
            finalColor->_b = std::min(255, finalColor->_b + color->_b);

            auto color2 = directionalLight.calculatePhongLighting(
                world2view,
                _vertices[i],
                _normals[i],
                baseColor,
                shininess,
                kd, ks, ka
            );

            finalColor->_r = std::min(255, finalColor->_r + color2->_r);
            finalColor->_g = std::min(255, finalColor->_g + color2->_g);
            finalColor->_b = std::min(255, finalColor->_b + color2->_b);
        }

        _vertexColors[i] = finalColor;
    }
}


