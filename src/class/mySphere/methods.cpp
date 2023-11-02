#include "mySphere.hpp"
#include "myTexture.hpp"

void mySphere::draw(myImage& I, std::vector<myLight *> L) {
    for (double u = 0; u < DPI; u += PRECISION) {
        for (double v = -PI2; v < PI2; v += PRECISION) {
            myVector3 pos(
                radius * my3d::cosf(v) * my3d::cosf(u) + center.x,
                radius * my3d::cosf(v) * my3d::sinf(u) + center.y,
                radius * my3d::sinf(v) + center.z
            );

            // Object
            myVector3 normal = pos - center;
            normal.normalize();
            myColor workingColor = hasTexture ? texture->getPixel(u / DPI, (v + PI / 2) / PI) : color;

            // Bump Map
            if (hasBumpMap) {
                double dhdu = 0;
                double dhdv = 0;
                bumpMap->bump(u / DPI, (v + PI / 2) / PI, dhdu, dhdv);

                myVector3 dMdu(
                    -radius * my3d::cosf(v) * my3d::sinf(u),
                    radius * my3d::cosf(v) * my3d::cosf(u),
                    0
                );

                myVector3 dMdv(
                    -radius * my3d::sinf(v) * my3d::cosf(u),
                    -radius * my3d::sinf(v) * my3d::sinf(u),
                    radius * my3d::cosf(v)
                );

                double K = 0.01;
                myVector3 bumpNormal = normal + (K * ((dMdu ^ (dhdv * normal)) + (dMdv ^ (dhdu * normal))));
                bumpNormal.normalize();
                normal = bumpNormal;
            }

            // Draw
            I.setPixel(pos, applyLighting(pos, normal, workingColor, L));
            // my3d::smallSleep(500);
        }
    }
}