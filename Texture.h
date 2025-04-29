//
// Created by Jacek on 29.04.2025.
//

#ifndef TEXTURE_H
#define TEXTURE_H
#include <algorithm>
#include <complex.h>
#include <vector>
#include <fstream>
#include <iostream>
#include "Color.h"


class Texture {
public:
    bool LoadFromTGA(const std::string &filename);
    int width, height;
    std::vector<Color> data;
};



#endif //TEXTURE_H
