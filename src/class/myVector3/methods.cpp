#include "3dengine.hpp"

double myVector3::dot(const myVector3& v) const {
    return x * v.x + y * v.y + z * v.z;
}

myVector3 myVector3::cross(const myVector3& v) const {
    return myVector3(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

double myVector3::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

double myVector3::squaredMagnitude() const {
    return x * x + y * y + z * z;
}

bool myVector3::isZero() const {
    return (std::abs(x) < EPSILON) && (std::abs(y) < EPSILON) && (std::abs(z) < EPSILON);
}

void myVector3::normalize() {
    if (isZero()) {
        return;
    }
    double m = magnitude();
    x /= m;
    y /= m;
    z /= m;
}

myVector3 myVector3::normalized() const {
    if (isZero()) {
        return myVector3();
    }
    double m = magnitude();
    return myVector3(x / m, y / m, z / m);
}

double myVector3::distanceTo(const myVector3& v) const {
    return std::sqrt(
        (x - v.x) * (x - v.x) +
        (y - v.y) * (y - v.y) +
        (z - v.z) * (z - v.z)
    );
}

double myVector3::squaredDistanceTo(const myVector3& v) const {
    return (x - v.x) * (x - v.x) +
           (y - v.y) * (y - v.y) +
           (z - v.z) * (z - v.z);
}

double myVector3::angleBetween(const myVector3& v) const {
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