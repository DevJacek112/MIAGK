//
// Created by Jacek on 20.03.2025.
//

#ifndef COLOR_H
#define COLOR_H
#include <algorithm>
#include <memory>


class Color {

public:

    int _r = 0;
    int _g = 0;
    int _b = 0;
    int _a = 0;

    Color(int r, int g, int b, int a);

    Color() = default;

    static std::shared_ptr<Color> Red()   { return std::make_shared<Color>(255, 0, 0, 122); }
    static std::shared_ptr<Color> Green() { return std::make_shared<Color>(0, 255, 0, 122); }
    static std::shared_ptr<Color> Blue()  { return std::make_shared<Color>(0, 0, 255, 122); }
    static std::shared_ptr<Color> White() { return std::make_shared<Color>(255, 255, 255, 122); }
    static std::shared_ptr<Color> Black() { return std::make_shared<Color>(0, 0, 0, 122); }



};

inline Color operator*(float scalar, const Color& color) {
    return Color(
        static_cast<uint8_t>(std::clamp(scalar * color._r, 0.0f, 255.0f)),
        static_cast<uint8_t>(std::clamp(scalar * color._g, 0.0f, 255.0f)),
        static_cast<uint8_t>(std::clamp(scalar * color._b, 0.0f, 255.0f)),
        color._a
    );
}

inline Color operator+(const Color& a, const Color& b) {
    return Color(
        std::min(255, a._r + b._r),
        std::min(255, a._g + b._g),
        std::min(255, a._b + b._b),
        std::min(255, a._a + b._a)
    );
}



#endif //COLOR_H
