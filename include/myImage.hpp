#pragma once

#include <iostream>
#include <limits>
#include <SFML/Graphics.hpp>

#include "constants.hpp"
#include "myColor.hpp"
#include "myPoint.hpp"
#include "myVector3.hpp"
#include "myShape.hpp"
#include "myLight.hpp"

class myShape;

class myImage {
    private:
        // ATTRIBUTES
        int width;
        int height;
        std::vector<myColor> pixels;
        std::vector<double> zBuffer;

    public:
        // CONSTRUCTORS
        myImage(int width = WINDOW_WIDTH, int height = WINDOW_HEIGHT, myColor const& c = myColor::BLACK);

        // SETTERS AND GETTERS
        int getWidth() const { return width; }
        int getHeight() const { return height; }

        // METHODS
        myColor getPixel(myPoint v);

        void setPixel(myPoint v, myColor const& c, double z = std::numeric_limits<double>::max());
        void setPixel(myVector3 v, myColor const& c);

        void clear(myColor const& c);

        void handleRayIntersection(int x, int z, myVector3 const& camera, myVector3 const& rayDirection, std::vector<myShape*> const& shapes, std::vector<myLight*> const& lights);
        void rayCast(myVector3 camera, std::vector<myShape*> const& shapes, std::vector<myLight*> const& lights);

        sf::Image toSFMLImage();

        void toPNG(std::string const& filename);
};