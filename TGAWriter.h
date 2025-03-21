//
// Created by Jacek on 20.03.2025.
//

#ifndef TGAWRITER_H
#define TGAWRITER_H

#include <memory>
#include <string>

#include "PixelBuffer.h"

class TGAWriter {
public:
    static void SaveToTGA(const std::string& filename, std::shared_ptr<PixelBuffer> pixelBuffer) ;
};

#endif // TGAWRITER_H
