#include "myParallelogram.hpp"

void myParallelogram::draw(myImage& I) {
    for (double u = 0; u < 1; u += PRECISION) {
        for(double v = 0; v < 1; v += PRECISION) {
            myVector3 pos3d = A + (u * (B - A)) + (v * (C - A));
            myPoint pos = myPoint(pos3d);

            I.setPixel(pos, color);
        }
    }
}