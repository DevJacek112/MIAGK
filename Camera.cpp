//
// Created by Jacek on 12.04.2025.
//

#include "Camera.h"


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

void Camera::RenderTriangle(const Triangle &triangle) {
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
