#include "3dengine.hpp"

myImage::myImage() {
    width = WINDOW_WIDTH;
    height = WINDOW_HEIGHT;
    pixels = new myColor[width * height];
}

myImage::myImage(int width, int height) {
    this->width = width;
    this->height = height;
    pixels = new myColor[width * height];
}

myImage::myImage(int width, int height, myColor c) {
    this->width = width;
    this->height = height;
    pixels = new myColor[width * height];
    clear(c);
}

myImage::~myImage() {
    delete[] pixels;
}