#pragma once

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

#include "myColor.hpp"

class myTexture {
    private:
        int width;
        int height;
        myColor *pixels;

        myColor interpolate(double u, double v);

    public:
        myTexture(const std::string& filename);
        myTexture();
        ~myTexture();

        myColor getPixel(double u, double v);
        void bump(double u, double v, double& dhdu, double& dhdv);
};