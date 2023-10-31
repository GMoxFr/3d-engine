#include "mySphere.hpp"

mySphere::mySphere(myVector3 c, double r, myColor clr, double diffuse) :
    center(c),
    radius(r),
    color(clr),
    hasTexture(false),
    hasBumpMap(false),
    diffuse(diffuse)
{};

mySphere::mySphere(myVector3 c, double r, std::string texture, double diffuse) :
    center(c),
    radius(r),
    hasTexture(true),
    hasBumpMap(false),
    diffuse(diffuse)
{
    this->texture = new myTexture(texture);
};

mySphere::~mySphere() {};