cmake_minimum_required(VERSION 3.30)
project(RepoMIAGK)

set(CMAKE_CXX_STANDARD 20)

add_executable(RepoMIAGK main.cpp
        PixelBuffer.cpp
        PixelBuffer.h
        Color.cpp
        Color.h
        TGAWriter.cpp
        TGAWriter.h
        Math/Float3.cpp
        Math/Float3.h
        Math/float4.cpp
        Math/float4.h
        Math/float4x4.cpp
        Math/float4x4.h
        Math/int3.cpp
        Math/int3.h
        Camera.cpp
        Camera.h
        Triangle.cpp
        Triangle.h
        Meshes/Mesh.cpp
        Meshes/Mesh.h
        Meshes/Cube.cpp
        Meshes/Cube.h
        Meshes/Cone.cpp
        Meshes/Cone.h
        Meshes/Cylinder.cpp
        Meshes/Cylinder.h
        Meshes/Torus.cpp
        Meshes/Torus.h
        Light/PointLight.cpp
        Light/PointLight.h
        VertexProcessor.cpp
        VertexProcessor.h
        Light/DirectionalLight.cpp
        Light/DirectionalLight.h
)
