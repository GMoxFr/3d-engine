#pragma once 

#include <cmath>
#include <random>
#include <string_view>
#include <algorithm>

#include "constants.hpp"
#include "myVector3.hpp"

//////////////////////////
// METHODS DECLARATION  //
//////////////////////////

enum class ArgumentType {
    HELP,
    SAVE,
    UNKNOWN
};

namespace my3d {
    double clamp(double v);
    double cosf(double theta);
    double sinf(double theta);
    double sqrtf(double x);
    void initRand();
    double randNP(double v);
    double randP(double v);
    void invertCoordSpherique(const myVector3& P3D, const myVector3& sphereCenter, double r, double& u, double& v);
    void smallSleep(int delay);
    bool isValidExtension(std::string_view filename, std::string_view extension);
    void displayHelp(std::string const& programName);
    bool handleSAVE(int& i, const char** argv, int argc, std::string& filename);
}