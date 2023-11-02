#pragma once

#include "myVector3.hpp"
#include "myLight.hpp"

class myAmbientLight : public myLight {
    private:
        double intensity;

    public:
        myAmbientLight(myColor clr, double intensity = 1.0) :
            myLight(clr),
            intensity(intensity)
        {};

        myColor applyLighting(myVector3 pos, myVector3 normal, myColor const& workingColor, double diffuse) override {
            (void)pos;
            (void)normal;
            (void)diffuse;
            return (color * intensity) * workingColor;
        };
};