#include "mySphere.hpp"

mySphere::mySphere(myVector3 c, double r, myColor clr, double diffuse) :
    myShape(clr, diffuse),
    center(c),
    radius(r)
{};

mySphere::mySphere(myVector3 c, double r, std::string texture, double diffuse) :
    myShape(texture, diffuse),
    center(c),
    radius(r)
{};

mySphere::~mySphere() {};