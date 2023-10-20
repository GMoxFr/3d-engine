#pragma once 

#include "myShape.hpp"
#include "myVector3.hpp"
#include "myColor.hpp"

class myParallelogram : public myShape {
    private:
        myVector3 A;
        myVector3 B;
        myVector3 C;
        myColor color;

    public:
        myParallelogram(myVector3 A, myVector3 B, myVector3 C, myColor clr);
        ~myParallelogram();

        void draw(myImage& I);
};