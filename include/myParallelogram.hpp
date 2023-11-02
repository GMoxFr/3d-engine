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
        myParallelogram(myVector3 A, myVector3 B, myVector3 C, myColor const& clr, double diffuse = 1.0);
        myParallelogram(myVector3 A, myVector3 B, myVector3 C, std::string const& texture, double diffuse = 1.0);
        ~myParallelogram() override = default;

        void draw(myImage& I, std::vector<myLight *> const& L) override;
        bool intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color, double &u, double &v) override;
};