#pragma once

#include "myVector3.hpp"
#include "myLight.hpp"

class myDirectionalLight : public myLight {
    private:
        myVector3 direction;
        double intensity;

    public:
        myDirectionalLight(myColor const& clr, myVector3 dir, double intensity = 1.0, myLightType t = myLightType::DIRECTIONAL) :
            myLight(clr, t),
            direction(dir),
            intensity(intensity)
        {
            direction.normalize();
        };

        myColor applyLighting(myVector3 pos, myVector3 normal, myColor const& workingColor, double diffuse) override {
            myColor result(0, 0, 0);

            // Diffuse Lighting
            double impact = my3d::clamp(normal * -direction);
            result += (getColor() * intensity) * workingColor * impact * diffuse;

            // Specular Lighting
            myVector3 reflectedLight = 2 * (-direction * normal) * normal + direction;
            myVector3 viewDirection = myVector3::CAMERA - pos;
            viewDirection.normalize();
            double k = 50.0;
            impact = my3d::clamp(reflectedLight * viewDirection);
            result += (getColor() * intensity) * std::pow(impact, k);

            return result;
        };

        myVector3 getDirection() const override { return direction; }
};