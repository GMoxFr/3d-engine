#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <cstdlib>
#include <thread>
#include <chrono>
#include <atomic>
#include <map>
#include <algorithm>
#include <string_view>

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

    std::map<std::string, ArgumentType, std::less<>> argumentMap = {
        {"-h", ArgumentType::HELP},
        {"--help", ArgumentType::HELP},
        {"-S", ArgumentType::SAVE},
        {"--save", ArgumentType::SAVE}
    };

    int i = 1;
    while (i < argc) {
        switch (std::string arg = argv[i]; argumentMap.count(arg) ? argumentMap[arg] : ArgumentType::UNKNOWN) {
            case ArgumentType::HELP:
                my3d::displayHelp(argv[0]);
                return 0;

            case ArgumentType::SAVE:
                if (!my3d::handleSAVE(i, (const char**)argv, argc, filename))
                    return 1;
                break;

            default:
                std::cout << "Error: Unknown argument " << arg << std::endl;
                std::cout << "Try '" << argv[0] << " --help' for more information" << std::endl;
                return 1;
        }
        i++;
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
    
    std::thread renderThread([&I, &filename]() {

        std::vector<myLight*> lights;
        lights.push_back(new myAmbientLight(myColor::WHITE, 0.1));
        lights.push_back(new myDirectionalLight(myColor::WHITE, myVector3(-1, 1, -1), 0.6));
        lights.push_back(new myDirectionalLight(myColor::WHITE, myVector3(1, 1, -1), 0.3));

        std::vector<myShape*> shapes;
        shapes.push_back(new mySphere(myVector3(WINDOW_WIDTH / 2, 1000, (WINDOW_HEIGHT / 2)), std::min(WINDOW_HEIGHT, WINDOW_WIDTH) / 3, "earth-8k.jpg")); // Earth
        shapes.push_back(new myTriangle(myVector3(WINDOW_WIDTH / 2, 500, WINDOW_HEIGHT / 2), myVector3((WINDOW_WIDTH / 2) + 130, 600, WINDOW_HEIGHT / 2), myVector3((WINDOW_WIDTH / 2), 600, (WINDOW_HEIGHT / 2) + 120), myColor::GREEN)); // Triangle
        shapes.push_back(new myParallelogram(myVector3::BOTTOM_LEFT, myVector3::BOTTOM_LEFT + (2000 * myVector3::FORWARD), myVector3::TOP_LEFT, myColor::GOLD)); // Left Wall
        shapes.push_back(new myParallelogram(myVector3::BOTTOM_RIGHT + (2000 * myVector3::FORWARD), myVector3::BOTTOM_RIGHT, myVector3::TOP_RIGHT + (2000 * myVector3::FORWARD), myColor::PURPLE)); // Right Wall
        shapes.push_back(new myParallelogram(myVector3::BOTTOM_LEFT, myVector3::BOTTOM_RIGHT, myVector3::BOTTOM_LEFT + (2000 * myVector3::FORWARD), myColor::CYAN)); // Floor
        shapes.push_back(new myParallelogram(myVector3::TOP_LEFT + (2000 * myVector3::FORWARD), myVector3::TOP_RIGHT + (2000 * myVector3::FORWARD), myVector3::TOP_LEFT, myColor::GREEN)); // Ceiling
        shapes.push_back(new myParallelogram(myVector3::BOTTOM_LEFT + (2000 * myVector3::FORWARD), myVector3::TOP_LEFT + (2000 * myVector3::FORWARD), myVector3::BOTTOM_RIGHT + (2000 * myVector3::FORWARD), myColor::PINK)); // Back Wall


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

    std::thread updateThread([&running, &texture, &I]() {
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