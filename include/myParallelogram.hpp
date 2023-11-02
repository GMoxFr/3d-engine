#pragma once 

#include "myShape.hpp"
#include "myVector3.hpp"
#include "myColor.hpp"
#include "myTexture.hpp"

class myParallelogram : public myShape {
    private:
        myVector3 A;
        myVector3 B;
        myVector3 C;

    public:
        myParallelogram(myVector3 A, myVector3 B, myVector3 C, myColor clr, double diffuse = 1.0);
        myParallelogram(myVector3 A, myVector3 B, myVector3 C, std::string texture, double diffuse = 1.0);
        ~myParallelogram();

        void draw(myImage& I, std::vector<myLight *> L);
};