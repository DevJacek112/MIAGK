//
// Created by Jacek on 12.04.2025.
//

#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <memory>

#include "Color.h"
#include "Math/Float3.h"


class Triangle {
public:
    float3 v1, v2, v3;
    std::shared_ptr<Color> v1Color, v2Color, v3Color;

    Triangle(const float3 &v1, const float3 &v2, const float3 &v3, const std::shared_ptr<Color> &v1_color,
        const std::shared_ptr<Color> &v2_color, const std::shared_ptr<Color> &v3_color)
        : v1(v1),
          v2(v2),
          v3(v3),
          v1Color(v1_color),
          v2Color(v2_color),
          v3Color(v3_color) {
    }
};



#endif //TRIANGLE_H
