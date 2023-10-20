#pragma once 

#include "myShape.hpp"
#include "myVector3.hpp"
#include "myColor.hpp"

class mySphere : public myShape {
    private:
        myVector3 center;
        double radius;
        myColor color;
        double diffuse;

    public:
        mySphere(myVector3 c, double r, myColor clr, double diffuse = 1.0);
        ~mySphere();

        void draw(myImage& I);
};