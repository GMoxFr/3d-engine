#include "myImage.hpp"

// Primary constructor with width, height, and color
myImage::myImage(int width, int height, myColor c) : width(width), height(height) {
    pixels = new myColor[width * height];
    zBuffer = new double[width * height];
    clear(c);
}

// Destructor
myImage::~myImage() {
    delete[] pixels;
    delete[] zBuffer;
}
