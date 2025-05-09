//
// Created by Jacek on 12.04.2025.
//

#include "Camera.h"

#include <memory>


Camera::Camera() {
    setPerspective(90.0f, 1.0f, 0.1f, 100.0f);

    _obj2world[0] = float4(1, 0, 0, 0);
    _obj2world[1] = float4(0, 1, 0, 0);
    _obj2world[2] = float4(0, 0, 1, 0);
    _obj2world[3] = float4(0, 0, 0, 1);
}

void Camera::setLookat(float3 eye, float3 center, float3 up) {
    float3 f = center - eye;
    f.Normalize();
    up.Normalize();
    float3 s = f.Cross(up);
    float3 u = s.Cross(f);
    _world2View[0] = float4(s[0], u[0], -f[0], 0);
    _world2View[1] = float4(s[1], u[1], -f[1], 0);
    _world2View[2] = float4(s[2], u[2], -f[2], 0);
    _world2View[3] = float4(0, 0, 0, 1);
    float4x4 m = float4x4(
        float4(1, 0, 0, 0),
        float4(0, 1, 0, 0),
        float4(0, 0, 1, 0),
        float4(-eye.x, -eye.y, -eye.z, 1)
    );
    _world2View = _world2View * m;
}

void Camera::setPerspective(float fovy, float aspect, float near, float far) {
    fovy *= M_PI / 360;
    float f = cos(fovy) / sin(fovy);
    float4 col0 = float4(f / aspect, 0.0f, 0.0f, 0.0f);
    float4 col1 = float4(0.0f, f, 0.0f, 0.0f);
    float4 col2 = float4(0.0f, 0.0f, (far + near) / (near - far), -1.0f);
    float4 col3 = float4(0.0f, 0.0f, (2 * far * near) / (near - far), 0.0f);

    _view2Proj = float4x4(col0, col1, col2, col3);

    /*for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << _view2Proj[i][j] << ", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;*/
}

void Camera::RenderTriangle(Triangle &triangle, const Mesh& mesh, float3 normal1, float3 normal2, float3 normal3, float3 pos1, float3 pos2, float3 pos3) {

    int i0 = triangle[0];
    int i1 = triangle[1];
    int i2 = triangle[2];

    float3 v0 = mesh._vertices[i0].position;
    float3 v1 = mesh._vertices[i1].position;
    float3 v2 = mesh._vertices[i2].position;

    auto c0 = mesh._vertices[i0].vertexColor;
    auto c1 = mesh._vertices[i1].vertexColor;
    auto c2 = mesh._vertices[i2].vertexColor;

    // lokal -> world
    float4 v0_world = float4(v0.x, v0.y, v0.z, 1.0f);
    float4 v1_world = float4(v1.x, v1.y, v1.z, 1.0f);
    float4 v2_world = float4(v2.x, v2.y, v2.z, 1.0f);

    // world -> view
    float4 v0_view = _world2View * v0_world;
    float4 v1_view = _world2View * v1_world;
    float4 v2_view = _world2View * v2_world;

    // view -> clip
    float4 v0_clip = _view2Proj * v0_view;
    float4 v1_clip = _view2Proj * v1_view;
    float4 v2_clip = _view2Proj * v2_view;

    // clip -> ndc
    float3 v0_ndc(v0_clip.x / v0_clip.w, v0_clip.y / v0_clip.w, v0_clip.z / v0_clip.w);
    float3 v1_ndc(v1_clip.x / v1_clip.w, v1_clip.y / v1_clip.w, v1_clip.z / v1_clip.w);
    float3 v2_ndc(v2_clip.x / v2_clip.w, v2_clip.y / v2_clip.w, v2_clip.z / v2_clip.w);

    _pixelBuffer->DrawTriangle(
        v0_ndc, c0,
        v1_ndc, c1,
        v2_ndc, c2,
        float3(0,0,0), float3(1,0,0), float3(0,1,0),
        mesh.textureNumber, normal1, normal2, normal3, std::make_shared<Mesh>(mesh), pos1, pos2, pos3);
}

void Camera::SetPixelBuffer(std::shared_ptr<PixelBuffer> pixelBuffer) {
    _pixelBuffer = pixelBuffer;
}

void Camera::RenderMeshes() {
    for (auto& mesh : _meshes) {
        for (auto& index : mesh->_indices) {
            int index0 = index.v1;
            int index1 = index.v2;
            int index2 = index.v3;

            float3 normal1 = mesh->_vertexProcessor->transformNormal(mesh->_vertices[index0].normal);
            float3 normal2 = mesh->_vertexProcessor->transformNormal(mesh->_vertices[index1].normal);
            float3 normal3 = mesh->_vertexProcessor->transformNormal(mesh->_vertices[index2].normal);

            /*std::cout << mesh->_vertices[index0].normal.x << " " << mesh->_vertices[index0].normal.y << " " << mesh->_vertices[index0].normal.z << std::endl;
            std::cout << normal2.x << " " << normal2.y << " " << normal2.z << std::endl;
            std::cout << normal3.x << " " << normal3.y << " " << normal3.z << std::endl;
            std::cout << std::endl;*/

            Triangle triangle(index0, index1, index2);

            RenderTriangle(triangle, *mesh,
                           normal1, normal2, normal3,
                           mesh->_vertices[index0].position,
                           mesh->_vertices[index1].position,
                           mesh->_vertices[index2].position);
        }
    }
}


