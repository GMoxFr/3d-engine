#include "mySphere.hpp"

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

bool mySphere::intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color, double &u, double &v) {

    double a = direction * direction;
    double b = 2 * direction * (origin - center);
    double d = origin * origin - 2 * origin * center + center * center - radius * radius;

    double delta = b * b - 4 * a * d;

    if (delta < 0) {
        return false;
    }
    double t1 = (-b - my3d::sqrtf(delta)) / (2 * a);
    double t2 = (-b + my3d::sqrtf(delta)) / (2 * a);

    if (t1 < 0 && t2 < 0)
        return false;
    if (t1 > 0 && t1 > 0)
        intersection = origin + t1 * direction;
    if (t1 < 0 && t2 > 0)
        intersection = origin + t2 * direction;

    normal = intersection - center;
    normal.normalize();
    color = this->color;
    my3d::invertCoordSpherique(intersection, this->center, this->radius, u, v);
    color = hasTexture ? texture->getPixel(u / DPI, (v + PI / 2) / PI) : this->color;

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

    return true;
}