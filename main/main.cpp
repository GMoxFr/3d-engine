#include <SFML/Graphics.hpp>

#include "3dengine.hpp"
#include "myImage.hpp"
#include "myPoint.hpp"
#include "myColor.hpp"
#include "mySphere.hpp"

int main(int argc, char** argv) {
    ///////////////////////
    // ARGUMENTS PARSING //
    ///////////////////////
    std::string filename;

    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            std::cout << "Usage: " << argv[0] << " [options]" << std::endl;
            std::cout << "Options:" << std::endl;
            std::cout << "  -h, --help\t\t\tShow this help message" << std::endl;
            std::cout << "  -S, --save <filename>\t\tSave the image to a PNG file" << std::endl;
            return 0;
        } else if (arg == "-S" || arg == "--save") {
            if (i + 1 < argc) {
                filename = argv[++i];

                std::string extension;
                if (filename.size() > 4) {
                    extension = filename.substr(filename.size() - 4);
                }

                if (extension != ".png" && extension != ".PNG") {
                    std::cout << "Error: The provided filename does not have a .png or .PNG extension." << std::endl;
                    return 1;
                }
            } else {
                std::cout << "Error: missing filename after " << arg << std::endl;
                return 1;
            }
        } else {
            std::cout << "Error: unknown argument " << arg << std::endl;
            std::cout << "Try '" << argv[0] << " --help' for more information" << std::endl;
            return 1;
        }
    }

    /////////////////////////
    // 3D Engine Test Code //
    /////////////////////////
    
    myImage I = myImage(WINDOW_WIDTH, WINDOW_HEIGHT, myColor(255, 255, 255, 255));

    mySphere s = mySphere(myVector3(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 300), 200, myColor(255, 0, 0, 255));
    s.draw(I);

    // for (int x = 0; x < WINDOW_WIDTH; x++) {
    //     myColor c = myColor(rand() % 256, rand() % 256, rand() % 256, 255);
    //     for (int y = 0; y < WINDOW_HEIGHT; y++) {
    //         myColor d = c.darken(1.0 - (double)y / WINDOW_HEIGHT);
    //         I.setPixel(myPoint(x, y), d);
    //     }
    // }

    if (!filename.empty()) {
        std::cout << "Saving image to " << filename << std::endl;
        I.toPNG(filename);
    }

    /////////////////////////
    // SFML initialization //
    /////////////////////////

    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D Engine");
    sf::Image image = I.toSFMLImage();
    sf::Texture texture;
    sf::Sprite sprite;

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
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