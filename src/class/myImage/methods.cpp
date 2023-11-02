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
    if (zBuffer[pos] < z) return;

    zBuffer[pos] = z;
    pixels[pos] = c;
}

void myImage::setPixel(myVector3 v, myColor c) {
    // Scramble the coordinates to match the subject's coordinate system
    setPixel(myPoint(v.x, v.z), c, v.y);
}

void myImage::rayCast(myVector3 camera, std::vector<myShape*> shapes, std::vector<myLight*> lights) {
    (void) lights;
    for(int x = 0; x < width; x++) {
        for(int z = 0; z < height; z++) {
            myVector3 rayDirection = myVector3(x, 0, z) - camera;
            rayDirection.normalize();

            myVector3 intersection;
            myVector3 normal;
            myColor color;

            double u;
            double v;

            for (myShape* shape : shapes) {
                if (shape->intersect(camera, rayDirection, intersection, normal, color, u, v)) {
                    myColor newColor = shape->applyLighting(intersection, normal, color, lights);

                    setPixel(myPoint(x, z), newColor, intersection.y);
                }
            }
        }
    }
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