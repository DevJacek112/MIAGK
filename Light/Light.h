//
// Created by Jacek on 1.05.2025.
//

#ifndef LIGHT_H
#define LIGHT_H

#include "../Math/float3.h"
#include "../Meshes/VertexProcessor.h"



class Light {
public:
    float3 position;
    float3 ambient;
    float3 diffuse;
    float3 specular;
    float shininess;

    Light(const float3 &position, const float3 &ambient, const float3 &diffuse, const float3 &specular,
          float shininess);

    virtual float3 calculate(VertexProcessor& vp, const float3& pointPosition, const float3& normal) = 0;
};



#endif //LIGHT_H
