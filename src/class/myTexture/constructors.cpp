#include "myTexture.hpp"

// Primary constructor with filename
myTexture::myTexture(const std::string &filename)
{
    sf::Image image;

    if (std::string path = "assets/textures/" + filename; !image.loadFromFile(path))
    {
        std::cout << CRED << "Error loading texture from file: " << path << CRESET << std::endl;
        error = true;
        return;
    }

    width = image.getSize().x;
    height = image.getSize().y;

    pixels = std::vector<myColor>(width * height);
    for (int x = 0; x < width; x++)
    {
        for (int y = height - 1; y >= 0; y--)
        {
            sf::Color c = image.getPixel(x, height - y - 1);
            pixels.at(x + y * width).fromSFMLColor(c);
        }
    }
}