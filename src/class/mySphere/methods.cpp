#include "mySphere.hpp"

void mySphere::draw(myImage& I) {
    for (double u = 0; u < DPI; u += PRECISION) {
        for (double v = -PI / 2; v < PI / 2; v += PRECISION) {
            double x3D = radius * my3d::cosf(v) * my3d::cosf(u) + center.x;
            double y3D = radius * my3d::cosf(v) * my3d::sinf(u) + center.y;
            double z3D = radius * my3d::sinf(v) + center.z;

            myVector3 pos3d = myVector3(x3D, y3D, z3D);

            myVector3 normal = pos3d - center;
            normal.normalize();
            myVector3 lightDirection = myVector3(1, -1, 1);
            lightDirection.normalize();
            myColor lightColor = myColor::WHITE;

            double intensity = normal * lightDirection;
            intensity = my3d::clamp(intensity);
            myColor newColor = (lightColor * color) * intensity * diffuse;
            newColor += myColor::AMBIENT_LIGHT * color;


            I.setPixel(pos3d, newColor);
        }
    }
}