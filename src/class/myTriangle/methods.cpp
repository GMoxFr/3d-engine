#include "myTriangle.hpp"

void myTriangle::draw(myImage& I, std::vector<myLight *> L) {
    for (double u = 0; u < 1; u += 0.001) {
        for(double v = 0; v < 1 - u; v += 0.001) {
            myVector3 pos = A + (u * (B - A)) + (v * (C - A));

            // Object
            myVector3 normal = (B - A) ^ (C - A);
            normal.normalize();
            myColor workingColor = hasTexture ? texture->getPixel(u, v) : color;

            // Bump Map
            if (hasBumpMap) {
                double dhdu = 0;
                double dhdv = 0;
                bumpMap->bump(u, v, dhdu, dhdv);

                myVector3 dMdu = B - A;
                myVector3 dMdv = C - A;

                double K = 0.01;
                myVector3 bumpNormal = normal + (K * ((dMdu ^ (dhdv * normal)) + (dMdv ^ (dhdu * normal))));
                bumpNormal.normalize();
                normal = bumpNormal;
            }

            // Draw
            I.setPixel(pos, applyLighting(pos, normal, workingColor, L));
        }
    }
}