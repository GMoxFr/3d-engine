#include "myTriangle.hpp"

myTriangle::myTriangle(myVector3 A, myVector3 B, myVector3 C, myColor const &clr, double diffuse, double fresnel, double reflection, double refraction) : myShape(clr, diffuse, fresnel, reflection, refraction),
                                                                                                                                                          A(A),
                                                                                                                                                          B(B),
                                                                                                                                                          C(C)
{
    precalculate();
};

myTriangle::myTriangle(myVector3 A, myVector3 B, myVector3 C, std::string const &texture, double diffuse, double fresnel, double reflection, double refraction) : myShape(texture, diffuse, fresnel, reflection, refraction),
                                                                                                                                                                  A(A),
                                                                                                                                                                  B(B),
                                                                                                                                                                  C(C)
{
    precalculate();
};