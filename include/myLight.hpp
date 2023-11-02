#pragma once

#include "myColor.hpp"

class myLight {
    protected:
        myColor color;

    public:
        myLight(myColor clr) :
            color(clr)
        {};

        virtual ~myLight() {};

        virtual myColor applyLighting(myVector3 pos, myVector3 normal, myColor const& workingColor, double diffuse) = 0;
};