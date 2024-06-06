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

int main(int argc, char **argv)
{
	//////////////////////
	// Argument Parsing //
	//////////////////////

	std::string saveFilename;
	std::string configFilename;
	int threads = 4;
	bool octree = false;
	bool display = true;

	if (my3d::argumentParser(argc, argv, configFilename, saveFilename, threads, octree, display) == 1)
	{
		return 1;
	}

	///////////////////////////
	// Global Initialization //
	///////////////////////////

	myImage I(WINDOW_WIDTH, WINDOW_HEIGHT, myColor::TRANSPARENT);
	sf::Texture texture;
	sf::Sprite sprite;

	std::vector<std::unique_ptr<myShape>> shapes;
	std::vector<std::unique_ptr<myLight>> lights;
	if (config::loadConfig(configFilename, shapes, lights, octree) == 1)
		return 1;

	sf::RenderWindow window;
	if (display)
		window.create(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Rendering : " + configFilename);

	std::atomic<bool> running = true;
	std::atomic<int> done = 0;
	std::atomic<bool> saving = true;
	std::vector<std::thread> renderThreads;

	int widthPerThread = WINDOW_WIDTH / threads;
	int leftoverPixels = WINDOW_WIDTH % threads;
	int extraPixelCount = 0;

	auto start = std::chrono::high_resolution_clock::now();

	int state = 0;
	my3d::SYSTEM_CLOCK_TIME_POINT lastUpdate = std::chrono::steady_clock::now();

	/////////////////////////////
	// 3D Engine Render Thread //
	/////////////////////////////

	for (int k = 0; k < threads; ++k)
	{
		int extraPixels = 0;
		if (extraPixelCount < leftoverPixels)
		{
			extraPixels = 1;
			extraPixelCount++;
		}

		int startX = k * widthPerThread;
		int endX = startX + widthPerThread + extraPixels;

		renderThreads.emplace_back([&I, &shapes, &lights, &done, startX, endX]()
								   {
            I.rayCast(myVector3::CAMERA, shapes, lights, startX, 0, endX, WINDOW_HEIGHT);
            done++; });
	}

	std::thread saveThread([&saving, &done, &I, &saveFilename, &threads, &start, &state, &lastUpdate]()
						   {
        while (saving.load())
        {
            my3d::renderingLog(state, lastUpdate);

            if (done == threads)
            {
                std::cout << CBLUE << "\rRendering took " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - start).count() << "ms" << CRESET << std::endl;
                if (!saveFilename.empty())
                {
                    std::cout << CPURPLE << "Saving image to " << saveFilename << CRESET << std::flush;
                    I.toPNG(saveFilename);
                    std::cout << CBLUE << "\r" << std::string(200, ' ') << "\r" << "Saved image to " << saveFilename << CRESET << std::endl;
                }
                saving = false;
            }
        } });

	//////////////////////////
	// Window Update Thread //
	//////////////////////////

	std::unique_ptr<std::thread> updateThread;

	if (display)
	{
		updateThread = std::make_unique<std::thread>([&running, &texture, &I]()
													 {
            while(running.load()) {
                std::this_thread::sleep_for(std::chrono::milliseconds(8));
                texture.loadFromImage(I.toSFMLImage());
            } });
	}

	/////////////////////////
	// SFML Window Handler //
	/////////////////////////

	if (display)
	{
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
				if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
					window.close();

			// Load image into texture and associate with sprite
			sprite.setTexture(texture, true);

			// Draw the sprite
			window.clear();
			window.draw(sprite);
			window.display();
		}
	}
	else
		while (done < threads)
			(void)0;

	/////////////////////////
	// Thread Termination  //
	/////////////////////////

	running = false;
	for (std::thread &renderThread : renderThreads)
		renderThread.join();
	if (updateThread && updateThread->joinable())
		updateThread->join();
	saveThread.join();

	return 0;
}