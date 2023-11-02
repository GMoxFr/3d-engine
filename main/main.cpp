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
        lights.push_back(new myDirectionalLight(myColor::WHITE, myVector3(-1, 1, -1), 0.6));
        lights.push_back(new myDirectionalLight(myColor::WHITE, myVector3(1, 1, -1), 0.3));

        std::vector<myShape*> shapes;
        shapes.push_back(new mySphere(myVector3(WINDOW_WIDTH / 2, 1000, (WINDOW_HEIGHT / 2)), std::min(WINDOW_HEIGHT, WINDOW_WIDTH) / 3, "earth-8k.jpg"));
        shapes.push_back(new myParallelogram(myVector3(0, 0, 0), myVector3(0, 2000, 0), myVector3(0, 0, WINDOW_HEIGHT - 1), "wood2.jpg")); // Left Wall
        shapes.push_back(new myParallelogram(myVector3(WINDOW_WIDTH - 1, 2000, 1), myVector3(WINDOW_WIDTH - 1, 1, 1), myVector3(WINDOW_WIDTH - 1, 2000, WINDOW_HEIGHT - 1), myColor::PURPLE)); // Right Wall
        shapes.push_back(new myParallelogram(myVector3(0, 0, 0), myVector3(WINDOW_WIDTH - 1, 1, 1), myVector3(0, 2000, 0), myColor::CYAN)); // Floor
        shapes.push_back(new myParallelogram(myVector3(0, 2000, WINDOW_HEIGHT - 1), myVector3(WINDOW_WIDTH - 1, 2000, WINDOW_HEIGHT - 1), myVector3(0, 0, WINDOW_HEIGHT - 1), myColor::MAGENTA)); // Ceiling
        shapes.push_back(new myParallelogram(myVector3(0, 2000, 0), myVector3(WINDOW_WIDTH - 1, 2000, 0), myVector3(0, 2000, WINDOW_HEIGHT - 1), myColor::SILVER)); // Back Wall
        shapes.push_back(new myTriangle(myVector3(WINDOW_WIDTH / 2, 500, WINDOW_HEIGHT / 2), myVector3((WINDOW_WIDTH / 2) + 130, 600, WINDOW_HEIGHT / 2), myVector3((WINDOW_WIDTH / 2), 600, (WINDOW_HEIGHT / 2) + 120), myColor::GREEN));

        shapes[0]->setBumpMap("bump2.png");

        // for (myShape* shape : shapes) {
        //     shape->draw(I, lights);
        // }

        I.rayCast(myVector3::CAMERA, shapes, lights);

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