#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "myColor.hpp"

class myTexture {
    private:
        int width;
        int height;
        std::vector<myColor> pixels;

        myColor interpolate(double u, double v) const;

    public:
        explicit myTexture(const std::string& filename);

        myColor getPixel(double u, double v) const;
        void bump(double u, double v, double& dhdu, double& dhdv) const;
};