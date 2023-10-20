#include "mySphere.hpp"

mySphere::mySphere(myVector3 c, double r, myColor clr, double diffuse) :
    center(c),
    radius(r),
    hasTexture(false),
    color(clr),
    diffuse(diffuse)
{};

mySphere::mySphere(myVector3 c, double r, std::string texture, double diffuse) :
    center(c),
    radius(r),
    hasTexture(true),
    texture(texture),
    diffuse(diffuse)
{};

mySphere::~mySphere() {};