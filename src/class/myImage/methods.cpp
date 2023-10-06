#include "myImage.hpp"

myColor myImage::getPixel(myPoint v) {
    if (v.x < 0 || v.x >= width || v.y < 0 || v.y >= height) {
        return myColor::BLACK;
    }
    return pixels[(height - v.y) * width + v.x];
}

void myImage::setPixel(myPoint v, myColor c, double z) {
    // This pos computation is needed in order to respect the origin being at the bottom left
    unsigned int pos = (height - v.y) * width + v.x;

    if (v.x < 0 || v.x >= width || v.y < 0 || v.y >= height) return;
    if (zBuffer[pos] > z) return;

    pixels[pos] = c;
}

void myImage::setPixel(myVector3 v, myColor c) {
    // Scramble the coordinates to match the subject's coordinate system
    setPixel(myPoint(v.x, v.z), c, v.y);
}

void myImage::clear(myColor c) {
    for (int i = 0; i < width * height; i++) {
        pixels[i] = c;
        zBuffer[i] = std::numeric_limits<double>::max();
    }
}

sf::Image myImage::toSFMLImage() {
    sf::Image image;
    image.create(width, height);

    for (int i = 0; i < width * height; i++) {
        image.setPixel(i % width, i / width, pixels[i].toSFMLColor());
    }

    return image;
}

void myImage::toPNG(std::string filename) {
    sf::Image image = toSFMLImage();
    image.saveToFile(filename);
}