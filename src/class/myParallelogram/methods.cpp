#include "myParallelogram.hpp"

void myParallelogram::draw(myImage& I, std::vector<std::unique_ptr<myLight>> const& L) {
    const int steps = 2000;
    for (int i = 0; i < steps; i++) {
        double u = static_cast<double>(i) / steps;
        for(int j = 0; j < steps; j++) {
            double v = static_cast<double>(j) / steps;
            
            myVector3 pos = A + (u * (B - A)) + (v * (C - A));

            // Object
            myVector3 normal = (B - A) ^ (C - A);
            normal.normalize();
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
                normal = bumpNormal;
            }

            // Draw
            I.setPixel(pos, applyLighting(pos, normal, workingColor, L, std::vector<std::unique_ptr<myShape>>()));
        }
    }
}

bool myParallelogram::intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color, double &u, double &v) {
    myVector3 AB = B - A;
    myVector3 AC = C - A;

    normal = AB ^ AC;
    normal.normalize();

    double t = ((A - origin) * normal) / (direction * normal);

    if (t < 0) {
        return false;
    }

    intersection = origin + (t * direction);

    myVector3 ABAC = AB ^ AC;
    myVector3 ACAB = AC ^ AB;

    u = ((AC ^ normal) * (intersection - A)) / ABAC.magnitude();
    v = ((AB ^ normal) * (A - intersection)) / ACAB.magnitude();

    if (u < 0 || u > 1 || v < 0 || v > 1)
        return false;
    
    color = getHasTexture() ? getTexture().getPixel(u, v) : getColor();

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
        normal = bumpNormal;
    }

    return true;
}