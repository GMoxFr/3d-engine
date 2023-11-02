#include "myVector3.hpp"

myVector3::myVector3(double x, double y, double z) : x(x), y(y), z(z) { }

myVector3::myVector3(const std::vector<double>& v) {
    x = (!v.empty()) ? v[0] : 0.0;
    y = (v.size() > 1) ? v[1] : 0.0;
    z = (v.size() > 2) ? v[2] : 0.0;
}