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

myColor myImage::handleBounce(myVector3 start, myVector3 rayDirection, std::unique_ptr<myShape> const& baseShape, std::vector<std::unique_ptr<myShape>> const& shapes, std::vector<std::unique_ptr<myLight>> const& lights, double index, int depth) {
    if (depth <= 0) return myColor::BLACK;

    myVector3 intersection;
    myVector3 normal;
    myColor color;

    double u;
    double v;

    for (std::unique_ptr<myShape> const& shape : shapes) {
        if (shape.get() == baseShape.get()) continue;

        if (shape->intersect(start, rayDirection, intersection, normal, color, u, v)) {
            myColor newColor = shape->applyLighting(intersection, normal, color, lights, shapes);
            if (shape->getReflection() > EPSILON) {
                myVector3 newDirection = rayDirection - normal * 2 * (rayDirection * normal);
                newColor += handleBounce(intersection, newDirection, shape, shapes, lights, shape->getFresnel(), depth - 1) * shape->getReflection();
            }
            if (shape->getRefraction() > EPSILON) {
                double n1 = index;
                double n2 = shape->getFresnel();
                double micro = n1 / n2;

                myVector3 refractedDir = micro * rayDirection + normal * (std::sqrt(1 - micro * micro * (1 - (normal * rayDirection) * (normal * rayDirection)))) - (micro * normal * (normal * rayDirection));
                newColor += handleBounce(intersection, refractedDir, shape, shapes, lights, shape->getFresnel(), depth - 1) * shape->getRefraction();
            }
            return newColor;
        }
    }

    return myColor::BLACK;
}

void myImage::handleRayIntersection(int x, int z, myVector3 const& camera, myVector3 const& rayDirection, std::vector<std::unique_ptr<myShape>> const& shapes, std::vector<std::unique_ptr<myLight>> const& lights) {
    myVector3 intersection;
    myVector3 normal;
    myColor color;

    double u;
    double v;

    for (std::unique_ptr<myShape> const& shape : shapes) {
        if (shape->intersect(camera, rayDirection, intersection, normal, color, u, v)) {
            myColor newColor = shape->applyLighting(intersection, normal, color, lights, shapes);
            if (shape->getReflection() > EPSILON) {
                myVector3 reflectionDir = rayDirection - normal * 2 * (rayDirection * normal);
                newColor += handleBounce(intersection, reflectionDir, shape, shapes, lights, 1.0, 6) * shape->getReflection();
            }
            if (shape->getRefraction() > EPSILON) {            
                double n1 = 1.0;
                double n2 = shape->getFresnel();
                double micro = n1 / n2;

                myVector3 refractedDir = micro * rayDirection + (-normal) * (std::sqrt(1 - micro * micro * (1 - ((-normal) * rayDirection) * ((-normal) * rayDirection)))) - (micro * (-normal) * ((-normal) * rayDirection));
                newColor += handleBounce(intersection, refractedDir, shape, shapes, lights, shape->getFresnel(), 6) * shape->getRefraction();
            }
            setPixel(myPoint(x, z), newColor, intersection.y);
        }
    }
}

void myImage::rayCast(myVector3 camera, std::vector<std::unique_ptr<myShape>> const& shapes, std::vector<std::unique_ptr<myLight>> const& lights) {
    for(int x = 0; x < width; x++) {
        for(int z = 0; z < height; z++) {
            myVector3 rayDirection = myVector3(x, 0, z) - camera;
            rayDirection.normalize();

            handleRayIntersection(x, z, camera, rayDirection, shapes, lights);
        }
    }
}

void myImage::rayCast(myVector3 camera, std::vector<std::unique_ptr<myShape>> const& shapes, std::vector<std::unique_ptr<myLight>> const& lights, int x1, int z1, int x2, int z2) {
    for(int x = x1; x < x2; x++) {
        for(int z = z1; z < z2; z++) {
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