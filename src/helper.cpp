#include <algorithm>
#include <thread>
#include <chrono>

#include "my3d.hpp"

namespace my3d {
    
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

    bool isValidExtension(std::string_view filename, std::string_view extension) {
        if (filename.size() <= extension.size()) return false;
        
        std::string_view fileExtension = filename.substr(filename.size() - extension.size());

        // Directly compare the string_views without converting to std::string
        return std::equal(fileExtension.begin(), fileExtension.end(),
                        extension.begin(), extension.end(),
                        [](char a, char b) {
                            return std::tolower(a) == std::tolower(b);
                        });
    }

    void displayHelp(std::string const& programName) {
        std::cout << "Usage: " << programName << " [options]" << std::endl;
        std::cout << "Options:" << std::endl;
        std::cout << "  -h, --help\t\t\tShow this help message" << std::endl;
        std::cout << "  -S, --save <filename>\t\tSave the image to a PNG file" << std::endl;
    }

    bool handleSAVE(int& i, const char** argv, int argc, std::string& filename) {
        i++;
        if (i < argc) {
            filename = argv[i];
            if (!my3d::isValidExtension(filename, ".png")) {
                std::cout << "Error: The provided filename does not have a .png or .PNG extension." << std::endl;
                return false;
            }
            return true;
        } else {
            std::cout << "Error: missing filename after " << argv[i-1] << std::endl;
            return false;
        }
    }

}