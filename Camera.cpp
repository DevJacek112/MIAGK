//
// Created by Jacek on 12.04.2025.
//

#include "Camera.h"

#include "VertexProcessor.h"


Camera::Camera() {
    setPerspective(90.0f, 1.0f, 0.1f, 100.0f);
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
}

void Camera::RenderTriangle(Triangle &triangle) {
    //local -> world
    float4 v1_world = triangle._obj2world * float4(triangle[0].x, triangle[0].y, triangle[0].z, -1.0f);
    float4 v2_world = triangle._obj2world * float4(triangle[1].x, triangle[1].y, triangle[1].z, -1.0f);
    float4 v3_world = triangle._obj2world * float4(triangle[2].x, triangle[2].y, triangle[2].z, -1.0f);

    //world -> view
    float4 v1_view = _world2View * v1_world;
    float4 v2_view = _world2View * v2_world;
    float4 v3_view = _world2View * v3_world;

    //view -> clip
    float4 v1_clip = _view2Proj * v1_view;
    float4 v2_clip = _view2Proj * v2_view;
    float4 v3_clip = _view2Proj * v3_view;

    //clip -> NDC (canon)
    float3 v1_ndc = float3(v1_clip.x / v1_clip.w, v1_clip.y / v1_clip.w, v1_clip.z / v1_clip.w);
    float3 v2_ndc = float3(v2_clip.x / v2_clip.w, v2_clip.y / v2_clip.w, v2_clip.z / v2_clip.w);
    float3 v3_ndc = float3(v3_clip.x / v3_clip.w, v3_clip.y / v3_clip.w, v3_clip.z / v3_clip.w);

    //world positions
    float3 v1_world_pos = float3(v1_world.x, v1_world.y, v1_world.z);
    float3 v2_world_pos = float3(v2_world.x, v2_world.y, v2_world.z);
    float3 v3_world_pos = float3(v3_world.x, v3_world.y, v3_world.z);

    //normals in world space
    float4 n1_world_temp = triangle._obj2world * float4(triangle.normal1.x, triangle.normal1.y, triangle.normal1.z, 0.0f);
    float3 n1_world(n1_world_temp.x, n1_world_temp.y, n1_world_temp.z);

    float4 n2_world_temp = triangle._obj2world * float4(triangle.normal2.x, triangle.normal2.y, triangle.normal2.z, 0.0f);
    float3 n2_world(n2_world_temp.x, n2_world_temp.y, n2_world_temp.z);

    float4 n3_world_temp = triangle._obj2world * float4(triangle.normal3.x, triangle.normal3.y, triangle.normal3.z, 0.0f);
    float3 n3_world(n3_world_temp.x, n3_world_temp.y, n3_world_temp.z);

    n1_world.Normalize();
    n2_world.Normalize();
    n3_world.Normalize();

    // material parameters
    float kd = 1.0f;
    float ks = 0.5f;
    float ka = 0.2f;
    float shininess = 32.0f;

    // final output colors
    auto v1Color = std::make_shared<Color>(0, 0, 0, 0);
    auto v2Color = std::make_shared<Color>(0, 0, 0, 0);
    auto v3Color = std::make_shared<Color>(0, 0, 0, 0);

    // point lights
    for (auto light : _pointLights) {
        auto v1LightColor = light.calculatePhongLighting(
            _world2View,
            v1_world_pos,
            n1_world,
            triangle._v1Color,
            shininess, kd, ks, ka
        );

        auto v2LightColor = light.calculatePhongLighting(
            _world2View,
            v2_world_pos,
            n2_world,
            triangle._v2Color,
            shininess, kd, ks, ka
        );

        auto v3LightColor = light.calculatePhongLighting(
            _world2View,
            v3_world_pos,
            n3_world,
            triangle._v3Color,
            shininess, kd, ks, ka
        );

        v1Color->_r = std::min(v1Color->_r + v1LightColor->_r, 255);
        v1Color->_g = std::min(v1Color->_g + v1LightColor->_g, 255);
        v1Color->_b = std::min(v1Color->_b + v1LightColor->_b, 255);

        v2Color->_r = std::min(v2Color->_r + v2LightColor->_r, 255);
        v2Color->_g = std::min(v2Color->_g + v2LightColor->_g, 255);
        v2Color->_b = std::min(v2Color->_b + v2LightColor->_b, 255);

        v3Color->_r = std::min(v3Color->_r + v3LightColor->_r, 255);
        v3Color->_g = std::min(v3Color->_g + v3LightColor->_g, 255);
        v3Color->_b = std::min(v3Color->_b + v3LightColor->_b, 255);
    }

    // directional light
    auto v1DirColor = _directionalLight.calculatePhongLighting(
        _world2View,
        v1_world_pos,
        n1_world,
        triangle._v1Color,
        shininess, kd, ks, ka
    );

    auto v2DirColor = _directionalLight.calculatePhongLighting(
        _world2View,
        v2_world_pos,
        n2_world,
        triangle._v2Color,
        shininess, kd, ks, ka
    );

    auto v3DirColor = _directionalLight.calculatePhongLighting(
        _world2View,
        v3_world_pos,
        n3_world,
        triangle._v3Color,
        shininess, kd, ks, ka
    );

    v1Color->_r = std::min(v1Color->_r + v1DirColor->_r, 255);
    v1Color->_g = std::min(v1Color->_g + v1DirColor->_g, 255);
    v1Color->_b = std::min(v1Color->_b + v1DirColor->_b, 255);

    v2Color->_r = std::min(v2Color->_r + v2DirColor->_r, 255);
    v2Color->_g = std::min(v2Color->_g + v2DirColor->_g, 255);
    v2Color->_b = std::min(v2Color->_b + v2DirColor->_b, 255);

    v3Color->_r = std::min(v3Color->_r + v3DirColor->_r, 255);
    v3Color->_g = std::min(v3Color->_g + v3DirColor->_g, 255);
    v3Color->_b = std::min(v3Color->_b + v3DirColor->_b, 255);

    // final colors
    triangle._v1Color = v1Color;
    triangle._v2Color = v2Color;
    triangle._v3Color = v3Color;

    // rasterize
    _pixelBuffer->DrawTriangle(v1_ndc, triangle._v1Color, v2_ndc, triangle._v2Color, v3_ndc, triangle._v3Color);
}


void Camera::SetPixelBuffer(std::shared_ptr<PixelBuffer> pixelBuffer) {
    _pixelBuffer = pixelBuffer;
}

void Camera::RenderMeshes() {
    for (auto mesh: _meshes) {
        for (auto& triangle: mesh->_triangles){
            RenderTriangle(triangle);
        }
    }
}
