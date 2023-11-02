#include "myPoint.hpp"

myPoint& myPoint::operator+=(const myPoint& p) {
    x += p.x;
    y += p.y;
    return *this;
}

myPoint& myPoint::operator-=(const myPoint& p) {
    x -= p.x;
    y -= p.y;
    return *this;
}

myPoint myPoint::operator+(const myPoint& p) const {
    return myPoint(
        x + p.x,
        y + p.y
    );
}

myPoint myPoint::operator-(const myPoint& p) const {
    return myPoint(
        x - p.x,
        y - p.y
    );
}

bool myPoint::operator==(const myPoint& p) const {
    return (x == p.x) && (y == p.y);
}

bool myPoint::operator!=(const myPoint& p) const {
    return !(*this == p);
}

bool myPoint::operator<(const myPoint& p) const {
    return (x < p.x) || ((x == p.x) && (y < p.y));
}

bool myPoint::operator>(const myPoint& p) const {
    return (x > p.x) || ((x == p.x) && (y > p.y));
}

bool myPoint::operator<=(const myPoint& p) const {
    return !(*this > p);
}

bool myPoint::operator>=(const myPoint& p) const {
    return !(*this < p);
}

myPoint myPoint::operator-() const {
    return myPoint(-x, -y);
}

std::ostream& operator<<(std::ostream& os, const myPoint& p) {
    os << "Point(" << p.x << ", " << p.y << ")";
    return os;
}