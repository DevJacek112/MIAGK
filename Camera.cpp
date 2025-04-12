//
// Created by Jacek on 12.04.2025.
//

#include "Camera.h"


Camera::Camera(){
    setPerspective(90.0f, 1.0f, 0.1f, 100.0f);
}

void Camera::setPerspective(float fovy, float aspect, float near, float far) {
    fovy *= M_PI/360;
    float f = cos(fovy)/sin(fovy);
    float4 col0 = float4(f / aspect, 0.0f, 0.0f, 0.0f);
    float4 col1 = float4(0.0f, f, 0.0f, 0.0f);
    float4 col2 = float4(0.0f, 0.0f, (far + near) / (near - far), -1.0f);
    float4 col3 = float4(0.0f, 0.0f, (2 * far * near) / (near - far), 0.0f);

    _projectionMatrix = float4x4(col0, col1, col2, col3);
}

void Camera::RenderTriangle(const Triangle& triangle) {

    float4 v1_clip = _projectionMatrix * float4(triangle.v1.x, triangle.v1.y, triangle.v1.z, 1.0f);
    float4 v2_clip = _projectionMatrix * float4(triangle.v2.x, triangle.v2.y, triangle.v2.z, 1.0f);
    float4 v3_clip = _projectionMatrix * float4(triangle.v3.x, triangle.v3.y, triangle.v3.z, 1.0f);

    float3 v1_ndc = float3((v1_clip.x / v1_clip.w), (v1_clip.y / v1_clip.w), (v1_clip.z / v1_clip.w));
    float3 v2_ndc = float3((v2_clip.x / v2_clip.w), (v2_clip.y / v2_clip.w), (v2_clip.z / v2_clip.w));
    float3 v3_ndc = float3((v3_clip.x / v3_clip.w), (v3_clip.y / v3_clip.w), (v3_clip.z / v3_clip.w));

    std::cout << v1_ndc.x << v1_ndc.y << v1_ndc.z << std::endl;
    _pixelBuffer->DrawTriangle(v1_ndc, triangle.v1Color, v2_ndc, triangle.v2Color, v3_ndc, triangle.v3Color);

}

void Camera::SetPixelBuffer(std::shared_ptr<PixelBuffer> pixelBuffer) {
    _pixelBuffer = pixelBuffer;
}
