cmake_minimum_required(VERSION 3.30)
project(RepoMIAGK)

set(CMAKE_CXX_STANDARD 20)

add_executable(RepoMIAGK main.cpp
        PixelBuffer.cpp
        PixelBuffer.h
        Color.cpp
        Color.h
        TGAWriter.cpp
        TGAWriter.h)
