//
// Created by Jacek on 20.03.2025.
//

#ifndef COLOR_H
#define COLOR_H
#include <memory>


class Color {

public:

    int _r = 0;
    int _g = 0;
    int _b = 0;
    int _a = 0;

    Color(int r, int g, int b, int a);

    static std::shared_ptr<Color> Red()   { return std::make_shared<Color>(255, 0, 0, 122); }
    static std::shared_ptr<Color> Green() { return std::make_shared<Color>(0, 255, 0, 122); }
    static std::shared_ptr<Color> Blue()  { return std::make_shared<Color>(0, 0, 255, 122); }
    static std::shared_ptr<Color> White() { return std::make_shared<Color>(255, 255, 255, 122); }
    static std::shared_ptr<Color> Black() { return std::make_shared<Color>(0, 0, 0, 122); }

};



#endif //COLOR_H
