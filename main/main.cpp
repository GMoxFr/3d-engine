#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <atomic>

#include "my3d.hpp"
#include "constants.hpp"
#include "myImage.hpp"
#include "myPoint.hpp"
#include "myColor.hpp"
#include "mySphere.hpp"
#include "myParallelogram.hpp"
#include "myTriangle.hpp"
#include "myTexture.hpp"
#include "myAmbientLight.hpp"
#include "myDirectionalLight.hpp"

int main(int argc, char** argv) {
    //////////////////////
    // Argument Parsing //
    //////////////////////

    std::string filename;
    std::string textureFilename;

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
        } else if (arg == "-l" || arg == "--load") {
            if (i + 1 < argc) {
                textureFilename = argv[++i];
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

    ///////////////////////////
    // Global Initialization //
    ///////////////////////////

    myImage I(WINDOW_WIDTH, WINDOW_HEIGHT, myColor::WHITE);
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D Engine");
    sf::Texture texture;
    sf::Sprite sprite;

    std::atomic<bool> running = true;

    /////////////////////////////
    // 3D Engine Render Thread //
    /////////////////////////////
    
    std::thread renderThread([&]() {

        std::vector<myLight*> lights;
        lights.push_back(new myAmbientLight(myColor::WHITE, 0.1));
        lights.push_back(new myDirectionalLight(myColor::WHITE, myVector3(1, -1, 1), 0.6));
        lights.push_back(new myDirectionalLight(myColor::WHITE, myVector3(-1, -1, 1), 0.3));

        std::vector<myShape*> shapes;
        shapes.push_back(new myParallelogram(myVector3(1, 1, 1), myVector3(1, 3000, WINDOW_HEIGHT / 2), myVector3(WINDOW_WIDTH - 1, 1, 1), myColor(0.8, 0.8, 0.8)));
        shapes.push_back(new myParallelogram(myVector3(1, 1, WINDOW_HEIGHT / 2), myVector3(1, 3000, WINDOW_HEIGHT), myVector3(WINDOW_WIDTH, 1, WINDOW_HEIGHT / 2), myColor(0.4, 0.4, 0.4)));
        shapes.push_back(new mySphere(myVector3(WINDOW_WIDTH / 2, 1000, (WINDOW_HEIGHT / 2)), std::min(WINDOW_HEIGHT, WINDOW_WIDTH) / 3, myColor(255, 0, 0, 255)));

        for (myShape* shape : shapes) {
            shape->draw(I, lights);
        }

        if (!textureFilename.empty()) {
            myTexture t(textureFilename);
            for (int x = 0; x < WINDOW_WIDTH; x++) {
                for (int y = 0; y < WINDOW_HEIGHT; y++) {
                    double u = (double)x / WINDOW_WIDTH;
                    double v = (double)y / WINDOW_HEIGHT;
                    I.setPixel(myPoint(x, y), t.getPixel(u, v));
                }
            }
        }

        if (!filename.empty()) {
            std::cout << "Saving image to " << filename << std::endl;
            I.toPNG(filename);
        }
    });

    //////////////////////////
    // Window Update Thread //
    //////////////////////////

    std::thread updateThread([&]() {
        while(running) {
            std::this_thread::sleep_for(std::chrono::milliseconds(8));
            texture.loadFromImage(I.toSFMLImage());
        }
    });

    /////////////////////////
    // SFML Window Handler //
    /////////////////////////

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                window.close();
            }
        }

        // Load image into texture and associate with sprite
        sprite.setTexture(texture, true);

        // Draw the sprite
        window.clear();
        window.draw(sprite);
        window.display();
    }

    /////////////////////////
    // Thread Termination  //
    /////////////////////////

    running = false;
    renderThread.join();
    updateThread.join();

    return 0;
}