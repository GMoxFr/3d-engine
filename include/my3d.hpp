#pragma once 

#include <cmath>
#include <random>

#include "constants.hpp"
#include "myVector3.hpp"

//////////////////////////
// METHODS DECLARATION  //
//////////////////////////

namespace my3d {
    double clamp(double v);
    double cosf(double theta);
    double sinf(double theta);
    double sqrtf(double x);
    void initRand();
    double randNP(double v);
    double randP(double v);
    void invertCoordSpherique(const myVector3& P3D, const myVector3& sphereCenter, double r, double& u, double& v);
}