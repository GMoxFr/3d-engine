#include "3dengine.hpp"

myVector2::myVector2() {
    x = 0.0;
    y = 0.0;
}

myVector2::myVector2(double x, double y) {
    this->x = x;
    this->y = y;
}

myVector2::myVector2(const myVector2& v) {
    x = v.x;
    y = v.y;
}

myVector2::myVector2(const std::vector<double>& v) {
    x = (v.size() > 0) ? v[0] : 0.0;
    y = (v.size() > 1) ? v[1] : 0.0;
}

myVector2::~myVector2() {
}
