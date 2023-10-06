#include "3dengine.hpp"

myPoint::myPoint() {
    x = 0;
    y = 0;
}

myPoint::myPoint(int x, int y) {
    this->x = x;
    this->y = y;
}

myPoint::myPoint(myVector2 v) {
    x = (int) v.x;
    y = (int) v.y;
}

myPoint::myPoint(myVector3 v) {
    x = (int) v.x;
    y = (int) v.z;
}

myPoint::~myPoint() {
}