#include "mySphere.hpp"

void mySphere::draw(myImage& I) {
    for (int i = 0; i < I.getWidth(); i++) {
        for (int j = 0; j < I.getHeight(); j++) {
            myPoint p(i, j);
            if (p.distance(myPoint(center)) <= radius) {
                I.setPixel(p, color, 1);
            }
        }
    }
}