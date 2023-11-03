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
#include <vector>
#include <fstream>
#include <nlohmann/json.hpp>

#include "my3d.hpp"
#include "config.hpp"
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

    std::string saveFilename;
    std::string configFilename;
    int threads = 4;

    if (my3d::argumentParser(argc, argv, configFilename, saveFilename, threads) == 1) {
        return 1;
    }

    ///////////////////////////
    // Global Initialization //
    ///////////////////////////

    myImage I(WINDOW_WIDTH, WINDOW_HEIGHT, myColor::WHITE);
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "3D Engine");
    sf::Texture texture;
    sf::Sprite sprite;
    
    std::vector<std::unique_ptr<myShape>> shapes;
    std::vector<std::unique_ptr<myLight>> lights;
    config::loadConfig(configFilename, shapes, lights);

    std::atomic<bool> running = true;
    std::atomic<int> done = 0;
    std::atomic<bool> saving = true;
    std::vector<std::thread> renderThreads;

    int widthPerThread = WINDOW_WIDTH / threads;
    int leftoverPixels = WINDOW_WIDTH % threads;
    int extraPixelCount = 0;

    auto start = std::chrono::high_resolution_clock::now();

    /////////////////////////////
    // 3D Engine Render Thread //
    /////////////////////////////

    for (int k = 0; k < threads; ++k) {
        int extraPixels = 0;
        if (extraPixelCount < leftoverPixels) {
            extraPixels = 1;
            extraPixelCount++;
        }

        int startX = k * widthPerThread;
        int endX = startX + widthPerThread + extraPixels;

        renderThreads.emplace_back([&I, &shapes, &lights, &done, startX, endX]() {
            I.rayCast(myVector3::CAMERA, shapes, lights, startX, 0, endX, WINDOW_HEIGHT);
            done++;
        });
    }

    std::thread saveThread([&saving, &done, &I, &saveFilename, &threads, &start]() {
        while (saving) {
            if (done == threads) {
                std::cout << "Rendering took " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << "ms" << std::endl;
                if (!saveFilename.empty()) {
                    std::cout << "Saving image to " << saveFilename << std::endl;
                    I.toPNG(saveFilename);
                }
                saving = false;
            }
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
    for (std::thread& renderThread : renderThreads)
        renderThread.join();
    updateThread.join();

    return 0;
}