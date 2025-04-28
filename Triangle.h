#ifndef TRIANGLE_H
#define TRIANGLE_H

class Triangle {
public:
    int _indices[3];

    Triangle(int i0, int i1, int i2) {
        _indices[0] = i0;
        _indices[1] = i1;
        _indices[2] = i2;
    }

    int operator[](int i) const {
        return _indices[i];
    }
};

#endif // TRIANGLE_H
