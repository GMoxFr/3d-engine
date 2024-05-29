#include "mySphere.hpp"

mySphere::mySphere(myVector3 c, double r, myColor const &clr, double diffuse, double fresnel, double reflection, double refraction) : myShape(clr, diffuse, fresnel, reflection, refraction),
                                                                                                                                      center(c),
                                                                                                                                      radius(r){};

mySphere::mySphere(myVector3 c, double r, std::string const &texture, double diffuse, double fresnel, double reflection, double refraction) : myShape(texture, diffuse, fresnel, reflection, refraction),
                                                                                                                                              center(c),
                                                                                                                                              radius(r){};