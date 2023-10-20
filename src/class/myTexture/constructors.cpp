#include "myTexture.hpp"

// Primary constructor with filename
myTexture::myTexture(const std::string& filename) {
    sf::Image image;

    std::string path = "assets/textures/" + filename;

    if (!image.loadFromFile(path)) {
        std::cout << "Error loading texture from file: " << path << std::endl;
        return;
    }

    width = image.getSize().x;
    height = image.getSize().y;

    pixels = new myColor[width * height];
    for (int x = 0; x < width; x++) {
        for (int y = height - 1; y >= 0; y--) {
            sf::Color c = image.getPixel(x, height - y - 1);
            pixels[x + y * width] = myColor(c.r, c.g, c.b, c.a);
        }
    }
}

// Destructor
myTexture::~myTexture() {
    delete[] pixels;
}