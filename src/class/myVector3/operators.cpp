#include "myVector3.hpp"

myVector3& myVector3::operator=(const myVector3& v) {
    if (this != &v) {
        x = v.x;
        y = v.y;
        z = v.z;
    }
    return *this;
}

myVector3& myVector3::operator+=(const myVector3& v) {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
}

myVector3& myVector3::operator-=(const myVector3& v) {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
}

myVector3& myVector3::operator*=(const double& d) {
    x *= d;
    y *= d;
    z *= d;
    return *this;
}

myVector3& myVector3::operator/=(const double& d) {
    if (std::abs(d) < EPSILON) {
        throw std::runtime_error("Division by zero or near-zero value");
    }
    x /= d;
    y /= d;
    z /= d;
    return *this;
}

myVector3 myVector3::operator+(const myVector3& v) const {
    return myVector3(
        x + v.x,
        y + v.y,
        z + v.z
    );
}

myVector3 myVector3::operator-(const myVector3& v) const {
    return myVector3(
        x - v.x,
        y - v.y,
        z - v.z
    );
}

myVector3 myVector3::operator*(const double& d) const {
    return myVector3(
        x * d,
        y * d,
        z * d
    );
}

myVector3 myVector3::operator/(const double& d) const {
    if (std::abs(d) < EPSILON) {
        throw std::runtime_error("Division by zero");
    }
    return myVector3(
        x / d,
        y / d,
        z / d
    );
}

bool myVector3::operator==(const myVector3& v) const {
    return x == v.x && y == v.y && z == v.z;
}

bool myVector3::operator!=(const myVector3& v) const {
    return x != v.x || y != v.y || z != v.z;
}

bool myVector3::operator<(const myVector3& v) const {
    return this->squaredMagnitude() < v.squaredMagnitude();
}

bool myVector3::operator>(const myVector3& v) const {
    return this->squaredMagnitude() > v.squaredMagnitude();
}

bool myVector3::operator<=(const myVector3& v) const {
    return this->squaredMagnitude() <= v.squaredMagnitude();
}

bool myVector3::operator>=(const myVector3& v) const {
    return this->squaredMagnitude() >= v.squaredMagnitude();
}

myVector3 operator*(const double& d, const myVector3& v) {
    return myVector3(
        v.x * d,
        v.y * d,
        v.z * d
    );
}

myVector3 myVector3::operator-() const {
    return myVector3(-x, -y, -z);
}

std::ostream& operator<<(std::ostream& os, const myVector3& v) {
    os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
    return os;
}