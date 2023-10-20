#pragma once 

#include "myShape.hpp"
#include "myVector3.hpp"
#include "myColor.hpp"

class mySphere : public myShape {
    private:
        myVector3 center;
        double radius;
        myColor color;

    public:
        mySphere(myVector3 c, double r, myColor clr);
        ~mySphere();

        void draw(myImage& I);
};