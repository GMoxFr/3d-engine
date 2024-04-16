#pragma once 

#include "myShape.hpp"
#include "myVector3.hpp"
#include "myColor.hpp"

class myTriangle : public myShape {
    private:
        myVector3 A;
        myVector3 B;
        myVector3 C; 
        
        myVector3 normal;
        myVector3 AB;
        myVector3 AC;

        double ABAC_magnitude;
        double ACAB_magnitude;

        myVector3 AB_normal;
        myVector3 AC_normal;

    public:
        myTriangle(myVector3 A, myVector3 B, myVector3 C, myColor const& clr, double diffuse = 1.0, double fresnel = 1.0, double reflection = 0.0, double refraction = 0.0);
        myTriangle(myVector3 A, myVector3 B, myVector3 C, std::string const& texture, double diffuse = 1.0, double fresnel = 1.0, double reflection = 0.0, double refraction = 0.0);
        ~myTriangle() override = default;

        void draw(myImage& I, std::vector<std::unique_ptr<myLight>> const& L) override;
        bool intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color, double &u, double &v) override;

        void precalculate();
};