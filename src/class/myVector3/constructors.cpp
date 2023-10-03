#include "3dengine.hpp"

myVector3::myVector3() {
    x = 0.0;
    y = 0.0;
    z = 0.0;
}

myVector3::myVector3(double x, double y, double z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

myVector3::myVector3(const myVector3& v) {
    x = v.x;
    y = v.y;
    z = v.z;
}

myVector3::myVector3(const std::vector<double>& v) {
    x = (v.size() > 0) ? v[0] : 0.0;
    y = (v.size() > 1) ? v[1] : 0.0;
    z = (v.size() > 2) ? v[2] : 0.0;
}

myVector3::~myVector3() {
}