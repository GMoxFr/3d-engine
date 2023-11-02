#pragma once

#include "myColor.hpp"

class myLight {
    private:
        myColor color;

    protected:
        const myColor& getColor() const { return color; }
        void setColor(myColor const& clr) { color = clr; }

    public:
        explicit myLight(myColor const& clr) :
            color(clr)
        {};

        virtual ~myLight() = default;

        virtual myColor applyLighting(myVector3 pos, myVector3 normal, myColor const& workingColor, double diffuse) = 0;
};