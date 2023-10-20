#pragma once 

#include "myShape.hpp"
#include "myVector3.hpp"
#include "myColor.hpp"

class myTriangle : public myShape {
    private:
        myVector3 A;
        myVector3 B;
        myVector3 C;
        myColor color;

    public:
        myTriangle(myVector3 A, myVector3 B, myVector3 C, myColor clr);
        ~myTriangle();

        void draw(myImage& I);
};