#include "mySphere.hpp"

void mySphere::draw(myImage& I) {
    for (double u = 0; u < DPI; u += PRECISION) {
        for (double v = -PI; v < PI; v += PRECISION) {
            double x3D = radius * my3d::cosf(v) * my3d::cosf(u) + center.x;
            double y3D = radius * my3d::cosf(v) * my3d::sinf(u) + center.y;
            double z3D = radius * my3d::sinf(v) + center.z;

            myVector3 pos3d = myVector3(x3D, y3D, z3D);
            myPoint pos = myPoint(pos3d);

            I.setPixel(pos, color);
        }
    }
}