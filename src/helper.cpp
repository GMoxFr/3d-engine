#include <algorithm>
#include <thread>
#include <chrono>

#include "my3d.hpp"

namespace my3d {

    static std::default_random_engine generator;

    double clamp(double v) {
        return std::max(0.0, std::min(1.0, v));
    }

    double cosf(double theta) {
        return std::cos(theta);
    }

    double sinf(double theta) {
        return std::sin(theta);
    }

    double sqrtf(double x) {
        return std::sqrt(x);
    }

    void initRand() {
        generator.seed(std::random_device()());
    }

    double randNP(double v) {
        std::uniform_real_distribution<double> distribution(-v, v);
        return distribution(generator);
    }

    double randP(double v) {
        std::uniform_real_distribution<double> distribution(0, v);
        return distribution(generator);
    }

    void invertCoordSpherique(const myVector3& P3D, const myVector3& sphereCenter, double r, double& u, double& v) {
        myVector3 p = P3D - sphereCenter;
        p = p / r;
        if (p.z >= 1) { u = PI2; v = 0; }
        else if (p.z <= -1) { u = -PI2; v = 0; }
        else {
            v = std::asin(p.z);
            double t = p.x / cosf(v);
            if (t <= -1) { u = PI; }
            else if (t >= 1) { u = 0; }
            else {
                if (p.y < 0) u = 2 * PI - std::acos(t);
                else u = std::acos(t);
            }
        }
    }

    void smallSleep(int delay) {
        auto start = std::chrono::high_resolution_clock::now();
        while (true) {
            auto now = std::chrono::high_resolution_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start);
            if (elapsed.count() > delay) {
                break;
            }
        }
    }

}