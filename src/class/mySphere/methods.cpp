#include "mySphere.hpp"
#include "myTexture.hpp"

void mySphere::draw(myImage& I) {
    for (double u = 0; u < DPI; u += PRECISION) {
        for (double v = -PI2; v < PI2; v += PRECISION) {
            myVector3 pos = myVector3(
                radius * my3d::cosf(v) * my3d::cosf(u) + center.x,
                radius * my3d::cosf(v) * my3d::sinf(u) + center.y,
                radius * my3d::sinf(v) + center.z
            );

            myVector3 normal = pos - center;
            normal.normalize();

            myVector3 lightDirection = myVector3(1, -1, 1);
            lightDirection.normalize();

            myColor lightColor = myColor::WHITE;

            myColor workingColor = hasTexture ? texture.getPixel(u / DPI, (v + PI / 2) / PI) : color;

            myColor newColor = (lightColor * workingColor) * my3d::clamp(normal * lightDirection) * diffuse;
            newColor += myColor::AMBIENT_LIGHT * workingColor;

            I.setPixel(pos, newColor);
            // my3d::smallSleep(200);
        }
    }
}