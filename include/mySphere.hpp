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
        mySphere(myVector3 c, double r, myColor const& clr, double diffuse = 1.0);
        mySphere(myVector3 c, double r, std::string const& texture, double diffuse = 1.0);

        void draw(myImage& I, std::vector<myLight *> const& L) override;
        bool intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color, double &u, double &v) override;
};