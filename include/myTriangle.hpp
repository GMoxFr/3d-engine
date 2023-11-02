#pragma once 

#include "myShape.hpp"
#include "myVector3.hpp"
#include "myColor.hpp"

class myTriangle : public myShape {
    private:
        myVector3 A;
        myVector3 B;
        myVector3 C;

    public:
        myTriangle(myVector3 A, myVector3 B, myVector3 C, myColor clr, double diffuse = 1.0);
        myTriangle(myVector3 A, myVector3 B, myVector3 C, std::string texture, double diffuse = 1.0);
        ~myTriangle();

        void draw(myImage& I, std::vector<myLight *> L);
        bool intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color, double &u, double &v) override;
};