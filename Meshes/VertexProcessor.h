//
// Created by Jacek on 1.05.2025.
//

#ifndef VECTORPROCESSOR_H
#define VECTORPROCESSOR_H
#include <memory>
#include <vector>

#include "../Math/float4x4.h"
#include "../Math/float3.h"


class Light;

class VertexProcessor {
public:
    float4x4 _view2proj;
    float4x4 _world2view;
    float4x4 _obj2world;
    std::vector<std::shared_ptr<Light>> lights;


    void addLight(std::shared_ptr<Light> light);

    const std::vector<std::shared_ptr<Light>> getLights() const;

    float3 transformNormal(const float3 &normal);
};



#endif //VECTORPROCESSOR_H
