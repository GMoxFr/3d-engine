#include "3dengine.hpp"

int main() {
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D Engine");

    // Image to hold pixel data
    sf::Image image;
    image.create(WINDOW_WIDTH, WINDOW_HEIGHT, sf::Color::Black);

    // Texture and sprite for rendering the image
    sf::Texture texture;
    sf::Sprite sprite;

    // Custom initialization
    myImage I = myImage(WINDOW_WIDTH, WINDOW_HEIGHT, myColor(0, 0, 0, 255));

    for (int x = 0; x < WINDOW_WIDTH; x++) {
        for (int y = 0; y < WINDOW_HEIGHT; y++) {
            float xNorm = (float)x / (float)WINDOW_WIDTH;
            float yNorm = (float)y / (float)WINDOW_HEIGHT;
            float xyNorm = (xNorm + yNorm) / 2.0f;
            I.setPixelColor(x, y, myColor(xNorm, yNorm, xyNorm, 1.0f));
        }
    }

    // Main loop
    while (window.isOpen()) {
        // Process events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Update image with pixel colors
        for (int y = 0; y < WINDOW_HEIGHT; ++y) {
            for (int x = 0; x < WINDOW_WIDTH; ++x) {
                image.setPixel(x, y, I.getPixelColor(x, y).toSFMLColor());
            }
        }

        // Load image into texture and associate with sprite
        texture.loadFromImage(image);
        sprite.setTexture(texture, true);

        // Draw the sprite
        window.clear();
        window.draw(sprite);
        window.display();
    }

    return 0;
}