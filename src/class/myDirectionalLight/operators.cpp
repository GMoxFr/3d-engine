#include "myDirectionalLight.hpp"

myDirectionalLight& myDirectionalLight::operator=(const myDirectionalLight& l) {
    direction = l.direction;
    color = l.color;
    intensity = l.intensity;
    return *this;
}