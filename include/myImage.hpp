#pragma once

#include <iostream>
#include <limits>
#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "myColor.hpp"
#include "myPoint.hpp"
#include "myVector3.hpp"

class myImage {
    private:
        // ATTRIBUTES
        int width;
        int height;
        myColor* pixels;
        double* zBuffer;

    public:
        // CONSTRUCTORS
        myImage(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT, myColor c = myColor::BLACK);
        ~myImage();

        // SETTERS AND GETTERS
        int getWidth() const { return width; }
        int getHeight() const { return height; }

        // METHODS
        myColor getPixel(myPoint v);

        void setPixel(myPoint v, myColor c, double z = std::numeric_limits<double>::max());
        void setPixel(myVector3 v, myColor c);

        void clear(myColor c);

        sf::Image toSFMLImage();

        void toPNG(std::string filename);
};