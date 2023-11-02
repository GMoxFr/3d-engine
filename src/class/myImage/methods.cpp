#include "myImage.hpp"

myColor myImage::getPixel(myPoint v) {
    if (v.x < 0 || v.x >= width || v.y < 0 || v.y >= height) {
        return myColor::BLACK;
    }
    return pixels.at((height - v.y) * width + v.x);
}

void myImage::setPixel(myPoint v, myColor const& c, double z) {
    if (v.x < 0 || v.x >= width || v.y < 0 || v.y >= height) return;

    unsigned int pos = (height - 1 - v.y) * width + v.x;
    
    if (zBuffer.at(pos) < z) return;

    zBuffer.at(pos) = z;
    pixels.at(pos) = c;
}


void myImage::setPixel(myVector3 v, myColor const& c) {
    setPixel(myPoint(static_cast<int>(round(v.x)), static_cast<int>(round(v.z))), c, v.y);
}

void myImage::handleRayIntersection(int x, int z, myVector3 const& camera, myVector3 const& rayDirection, std::vector<myShape*> const& shapes, std::vector<myLight*> const& lights) {
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

void myImage::rayCast(myVector3 camera, std::vector<myShape*> const& shapes, std::vector<myLight*> const& lights) {
    for(int x = 0; x < width; x++) {
        for(int z = 0; z < height; z++) {
            myVector3 rayDirection = myVector3(x, 0, z) - camera;
            rayDirection.normalize();

            handleRayIntersection(x, z, camera, rayDirection, shapes, lights);
        }
    }
}

void myImage::clear(myColor const& c) {
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

void myImage::toPNG(std::string const& filename) {
    sf::Image image = toSFMLImage();
    image.saveToFile(filename);
}