#pragma once 

#include "myShape.hpp"
#include "myVector3.hpp"
#include "myColor.hpp"
#include "myTexture.hpp"

class mySphere : public myShape {
    private:
        myVector3 center;
        double radius;

    public:
        mySphere(myVector3 c, double r, myColor clr, double diffuse = 1.0);
        mySphere(myVector3 c, double r, std::string texture, double diffuse = 1.0);
        ~mySphere();

        void draw(myImage& I, std::vector<myLight *> L);
};