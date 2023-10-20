#include "myDirectionalLight.hpp"

myDirectionalLight::myDirectionalLight() : direction(myVector3(0, 0, 0)), color(myColor::WHITE), intensity(1.0) { }
myDirectionalLight::myDirectionalLight(const myVector3 direction, const myColor color, double intensity) : direction(direction), color(color), intensity(intensity) { }
myDirectionalLight::myDirectionalLight(const myDirectionalLight& l) : direction(l.direction), color(l.color), intensity(l.intensity) { }
myDirectionalLight::~myDirectionalLight() { }