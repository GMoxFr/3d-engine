#include "myParallelogram.hpp"

void myParallelogram::draw(myImage& I, std::vector<std::unique_ptr<myLight>> const& L) {
    const int steps = 2000;
    for (int i = 0; i < steps; i++) {
        double u = static_cast<double>(i) / steps;
        for(int j = 0; j < steps; j++) {
            double v = static_cast<double>(j) / steps;
            
            myVector3 pos = A + (u * (B - A)) + (v * (C - A));

            // Object
            // myVector3 normal = (B - A) ^ (C - A);
            // normal.normalize();
            myVector3 usingNormal = normal;

            myColor workingColor = getHasTexture() ? getTexture().getPixel(u, v) : getColor();

            // Bump Map
            if (getHasBumpMap()) {
                double dhdu = 0;
                double dhdv = 0;
                getBumpMap().bump(u, v, dhdu, dhdv);

                myVector3 dMdu = B - A;
                myVector3 dMdv = C - A;

                double K = 0.01;
                myVector3 bumpNormal = normal + (K * ((dMdu ^ (dhdv * normal)) + (dMdv ^ (dhdu * normal))));
                bumpNormal.normalize();
                usingNormal = bumpNormal;
            }

            // Draw
            I.setPixel(pos, applyLighting(pos, usingNormal, workingColor, L, std::vector<std::unique_ptr<myShape>>()));
        }
    }
}

bool myParallelogram::intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color, double &u, double &v) {
    normal = this->normal;

    if (std::abs(direction * normal) < EPSILON) {
        return false;
    }

    double t = ((A - origin) * normal) / (direction * normal);

    if (t < 0) {
        return false;
    }

    intersection = origin + (t * direction);

    u = (AC_normal * (intersection - A)) / ABAC_magnitude;
    v = (AB_normal * (A - intersection)) / ACAB_magnitude;

    if (u < 0 || u > 1 || v < 0 || v > 1)
        return false;
    
    color = hasTexture ? texture->getPixel(u, v) : getColor();

    // Bump Map
    if (hasBumpMap) {
        double dhdu, dhdv;
        bumpMap->bump(u, v, dhdu, dhdv);
        normal = normal + (0.01 * (((B - A) ^ (dhdv * normal)) + ((C - A) ^ (dhdu * normal))));
        normal.normalize();
    }

    return true;
}

bool myParallelogram::intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color) {
    normal = this->normal;

    if (std::abs(direction * normal) < EPSILON) {
        return false;
    }

    double t = ((A - origin) * normal) / (direction * normal);

    if (t < 0) {
        return false;
    }

    intersection = origin + (t * direction);

    double u = (AC_normal * (intersection - A)) / ABAC_magnitude;
    double v = (AB_normal * (A - intersection)) / ACAB_magnitude;

    if (u < 0 || u > 1 || v < 0 || v > 1)
        return false;
    
    color = hasTexture ? texture->getPixel(u, v) : getColor();

    // Bump Map
    if (hasBumpMap) {
        double dhdu, dhdv;
        bumpMap->bump(u, v, dhdu, dhdv);
        normal = normal + (0.01 * (((B - A) ^ (dhdv * normal)) + ((C - A) ^ (dhdu * normal))));
        normal.normalize();
    }

    return true;
}

bool myParallelogram::intersect(myVector3 const& origin, myVector3 const& direction) {
    if (std::abs(direction * normal) < EPSILON) {
        return false;
    }

    double t = ((A - origin) * normal) / (direction * normal);

    if (t < 0) {
        return false;
    }

    myVector3 intersection = origin + (t * direction);

    double u = (AC_normal * (intersection - A)) / ABAC_magnitude;
    double v = (AB_normal * (A - intersection)) / ACAB_magnitude;

    return u >= 0 && u <= 1 && v >= 0 && v <= 1;
}

double myParallelogram::intersectDistance(myVector3 const& origin, myVector3 const& direction) {
    if (std::abs(direction * normal) < EPSILON) {
        return -1;
    }

    double t = ((A - origin) * normal) / (direction * normal);

    if (t < 0) {
        return -1;
    }

    myVector3 intersection = origin + (t * direction);

    double u = (AC_normal * (intersection - A)) / ABAC_magnitude;
    double v = (AB_normal * (A - intersection)) / ACAB_magnitude;

    if (u < 0 || u > 1 || v < 0 || v > 1)
        return -1;

    return t;
}

void myParallelogram::precalculate() {
    normal = (B - A) ^ (C - A);
    normal.normalize();

    AB = B - A;
    AC = C - A;

    ABAC_magnitude = (AB ^ AC).magnitude();
    ACAB_magnitude = (AC ^ AB).magnitude();

    AB_normal = AB ^ normal;
    AC_normal = AC ^ normal;
}