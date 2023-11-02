#include "myTriangle.hpp"

myTriangle::myTriangle(myVector3 A, myVector3 B, myVector3 C, myColor const& clr, double diffuse) :
    myShape(clr, diffuse),
    A(A),
    B(B),
    C(C)
{};

myTriangle::myTriangle(myVector3 A, myVector3 B, myVector3 C, std::string const& texture, double diffuse) :
    myShape(texture, diffuse),
    A(A),
    B(B),
    C(C)
{};