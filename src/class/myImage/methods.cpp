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

void myImage::setPixelColor(myPoint v, myColor c, double y) {
    if (v.x < 0 || v.x >= width || v.y < 0 || v.y >= height) {
        return;
    }
    if(yBuffer[(int)v.y * width + (int)v.x] < y || yBuffer[(int)v.y * width + (int)v.x] == -1.0) {
        pixels[(int)v.y * width + (int)v.x] = c;
        yBuffer[(int)v.y * width + (int)v.x] = y;
    }
}

void myImage::setPixelColor(int x, int y, myColor c) {
    myImage::setPixelColor(myPoint(x, y), c, 0.0);
}

void myImage::setPixelColor(myVector2 v, myColor c) {
    myImage::setPixelColor(myPoint(v), c, 0.0);
}

void myImage::setPixelColor(myVector3 v, myColor c) {
    myImage::setPixelColor(myPoint(v), c, v.y);
}

void myImage::clear(myColor c) {
    for (int i = 0; i < width * height; i++) {
        pixels[i] = c;
        yBuffer[i] = -1.0;
    }
}