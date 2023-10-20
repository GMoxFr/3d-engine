#include "myPoint.hpp"

myPoint::myPoint() : myPoint(0, 0) { }

myPoint::myPoint(int x, int y) : x(x), y(y) { }

myPoint::myPoint(myVector3 v) : myPoint(static_cast<int>(round(v.x)), static_cast<int>(round(v.y))) { }

myPoint::myPoint(const myPoint& p) : myPoint(p.x, p.y) { }

myPoint::~myPoint() { }