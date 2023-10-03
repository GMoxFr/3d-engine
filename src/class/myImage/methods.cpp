#include "3dengine.hpp"

myColor myImage::getPixelColor(int x, int y) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return myColor(0, 0, 0, 0);
    }
    return pixels[y * width + x];
}

myColor myImage::getPixelColor(myVector2 v) {
    if (v.x < 0 || v.x >= width || v.y < 0 || v.y >= height) {
        return myColor(0, 0, 0, 0);
    }
    return pixels[(int)v.y * width + (int)v.x];
}

void myImage::setPixelColor(int x, int y, myColor c) {
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return;
    }
    pixels[y * width + x] = c;
}

void myImage::setPixelColor(myVector2 v, myColor c) {
    if (v.x < 0 || v.x >= width || v.y < 0 || v.y >= height) {
        return;
    }
    pixels[(int)v.y * width + (int)v.x] = c;
}

void myImage::clear(myColor c) {
    for (int i = 0; i < width * height; i++) {
        pixels[i] = c;
    }
}