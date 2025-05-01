//
// Created by Jacek on 1.05.2025.
//

#include "Light.h"

Light::Light(const float3 &position, const float3 &ambient, const float3 &diffuse, const float3 &specular,
             float shininess) : position(position), ambient(ambient), diffuse(diffuse), specular(specular),
                                shininess(shininess) {}