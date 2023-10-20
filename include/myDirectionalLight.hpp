#pragma once

#include "myVector3.hpp"
#include "myColor.hpp"

class myDirectionalLight {
    private:

    public:
        // ATTRIBUTES
        myVector3 direction;
        myColor color;
        double intensity;

        // CONSTRUCTORS
        myDirectionalLight();
        myDirectionalLight(const myVector3 direction, const myColor color, double intensity = 1.0);
        myDirectionalLight(const myDirectionalLight& l);
        ~myDirectionalLight();

        // OPERATORS
        myDirectionalLight& operator=(const myDirectionalLight& l);
};