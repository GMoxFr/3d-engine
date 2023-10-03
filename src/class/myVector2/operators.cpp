#include "3dengine.hpp"

myVector2& myVector2::operator=(const myVector2& v) {
    if (this != &v) {
        x = v.x;
        y = v.y;
    }
    return *this;
}

myVector2& myVector2::operator+=(const myVector2& v) {
    x += v.x;
    y += v.y;
    return *this;
}

myVector2& myVector2::operator-=(const myVector2& v) {
    x -= v.x;
    y -= v.y;
    return *this;
}

myVector2& myVector2::operator*=(const double& d) {
    x *= d;
    y *= d;
    return *this;
}

myVector2& myVector2::operator/=(const double& d) {
    x /= d;
    y /= d;
    return *this;
}

myVector2 myVector2::operator+(const myVector2& v) const {
    return myVector2(
        x + v.x,
        y + v.y
    );
}

myVector2 myVector2::operator-(const myVector2& v) const {
    return myVector2(
        x - v.x,
        y - v.y
    );
}

myVector2 myVector2::operator*(const double& d) const {
    return myVector2(
        x * d,
        y * d
    );
}

myVector2 myVector2::operator/(const double& d) const {
    return myVector2(
        x / d,
        y / d
    );
}

bool myVector2::operator==(const myVector2& v) const {
    return x == v.x && y == v.y;
}

bool myVector2::operator!=(const myVector2& v) const {
    return x != v.x || y != v.y;
}

bool myVector2::operator<(const myVector2& v) const {
    return this->squaredMagnitude() < v.squaredMagnitude();
}

bool myVector2::operator>(const myVector2& v) const {
    return this->squaredMagnitude() > v.squaredMagnitude();
}

bool myVector2::operator<=(const myVector2& v) const {
    return this->squaredMagnitude() <= v.squaredMagnitude();
}

bool myVector2::operator>=(const myVector2& v) const {
    return this->squaredMagnitude() >= v.squaredMagnitude();
}

myVector2 operator*(const double& d, const myVector2& v) {
    return myVector2(
        v.x * d,
        v.y * d
    );
}

myVector2 myVector2::operator-() const {
    return myVector2(-x, -y);
}

std::ostream& operator<<(std::ostream& os, const myVector2& v) {
    os << "Vector2(" << v.x << ", " << v.y << ")";
    return os;
}
