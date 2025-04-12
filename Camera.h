//
// Created by Jacek on 12.04.2025.
//

#ifndef CAMERA_H
#define CAMERA_H
#include <math.h>

#include "PixelBuffer.h"
#include "Triangle.h"
#include "Math/float4x4.h"


class Camera {
    public:
    float4x4 _projectionMatrix;
    std::shared_ptr<PixelBuffer> _pixelBuffer;

    Camera();

    void setPerspective(float fovy, float aspect, float near, float far);

    void RenderTriangle(const Triangle& triangle);

    void SetPixelBuffer(std::shared_ptr<PixelBuffer> pixelBuffer);

};



#endif //CAMERA_H
