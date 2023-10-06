#include <algorithm>

#include "3dengine.hpp"

namespace my3d {

    double clamp(double v) {
        return std::max(0.0, std::min(1.0, v));
    }

}