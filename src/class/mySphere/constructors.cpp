#include "mySphere.hpp"

mySphere::mySphere(myVector3 c, double r, myColor const& clr, double diffuse) :
    myShape(clr, diffuse),
    center(c),
    radius(r)
{};

mySphere::mySphere(myVector3 c, double r, std::string const& texture, double diffuse) :
    myShape(texture, diffuse),
    center(c),
    radius(r)
{};