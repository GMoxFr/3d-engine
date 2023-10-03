#include "3dengine.hpp"

double myVector2::dot(const myVector2& v) const {
    return x * v.x + y * v.y;
}

double myVector2::magnitude() const {
    return std::sqrt(x * x + y * y);
}

double myVector2::squaredMagnitude() const {
    return x * x + y * y;
}

bool myVector2::isZero() const {
    return (std::abs(x) < EPSILON) && (std::abs(y) < EPSILON);
}

void myVector2::normalize() {
    if (isZero()) {
        return;
    }
    double m = magnitude();
    x /= m;
    y /= m;
}

myVector2 myVector2::normalized() const {
    if (isZero()) {
        return myVector2();
    }
    double m = magnitude();
    return myVector2(x / m, y / m);
}

double myVector2::distanceTo(const myVector2& v) const {
    return std::sqrt(
        (x - v.x) * (x - v.x) +
        (y - v.y) * (y - v.y)
    );
}

double myVector2::squaredDistanceTo(const myVector2& v) const {
    return (x - v.x) * (x - v.x) +
           (y - v.y) * (y - v.y);
}

double myVector2::angleBetween(const myVector2& v) const {
    double dotProduct = this->dot(v);

    double magA = this->magnitude();
    double magB = v.magnitude();

    if (std::abs(magA) < EPSILON || std::abs(magB) < EPSILON) {
        return 0.0;
    }

    double cosineValue = dotProduct / (magA * magB);
    cosineValue = std::max(-1.0, std::min(1.0, cosineValue));

    return std::acos(cosineValue);
}
