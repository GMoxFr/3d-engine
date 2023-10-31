#include "mySphere.hpp"
#include "myTexture.hpp"

void mySphere::setBumpMap(std::string filename) {
    hasBumpMap = true;
    bumpMap = new myTexture(filename);
}

void mySphere::draw(myImage& I) {
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

                // Compute tangents based on partial derivatives
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

            // Light
            myVector3 lightDirection(1, -1, 1);
            lightDirection.normalize();
            myColor lightColor = myColor::WHITE;
            
            // Ambient Lighting
            myColor newColor = myColor::AMBIENT_LIGHT * workingColor;

            // Diffuse Lighting
            double intensity = my3d::clamp(normal * lightDirection);
            newColor += (lightColor * workingColor) * intensity * diffuse;

            // Specular Lighting
            // double alpha = normal.angleBetween(lightDirection);
            // myVector3 reflectedLight2 = my3d::cosf(alpha) * normal + (-lightDirection);
            myVector3 reflectedLight = 2 * (lightDirection * normal) * normal - lightDirection;
            myVector3 viewDirection = myVector3::CAMERA - pos;
            viewDirection.normalize();
            double k = 50.0;
            double intensityS = my3d::clamp(reflectedLight * viewDirection);
            myColor specularColor = lightColor * std::pow(intensityS, k);
            newColor += specularColor;

            // Draw
            I.setPixel(pos, newColor);
            // my3d::smallSleep(500);
        }
    }
}