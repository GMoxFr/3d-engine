#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include <nlohmann/json.hpp>

#include "my3d.hpp"

namespace my3d
{

	double clamp(double v)
	{
		return std::max(0.0, std::min(1.0, v));
	}

	double cosf(double theta)
	{
		return std::cos(theta);
	}

	double sinf(double theta)
	{
		return std::sin(theta);
	}

	double sqrtf(double x)
	{
		return std::sqrt(x);
	}

	void invertCoordSpherique(const myVector3 &P3D, const myVector3 &sphereCenter, double r, double &u, double &v)
	{
		myVector3 p = P3D - sphereCenter;
		p = p / r;
		if (p.z >= 1)
		{
			u = PI2;
			v = 0;
		}
		else if (p.z <= -1)
		{
			u = -PI2;
			v = 0;
		}
		else
		{
			v = std::asin(p.z);
			double t = p.x / cosf(v);
			if (t <= -1)
			{
				u = PI;
			}
			else if (t >= 1)
			{
				u = 0;
			}
			else
			{
				if (p.y < 0)
					u = 2 * PI - std::acos(t);
				else
					u = std::acos(t);
			}
		}
	}

	void smallSleep(int delay)
	{
		auto start = std::chrono::high_resolution_clock::now();
		while (true)
		{
			auto now = std::chrono::high_resolution_clock::now();
			auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start);
			if (elapsed.count() > delay)
			{
				break;
			}
		}
	}

	bool isValidExtension(std::string_view filename, std::string_view extension)
	{
		if (filename.size() <= extension.size())
			return false;

		std::string_view fileExtension = filename.substr(filename.size() - extension.size());

		return std::equal(fileExtension.begin(), fileExtension.end(),
						  extension.begin(), extension.end(),
						  [](char a, char b)
						  {
							  return std::tolower(a) == std::tolower(b);
						  });
	}

	void displayHelp(std::string const &programName)
	{
		std::cout << CYELLOW << "Usage: " << programName << CGREEN << " <arguments>" << CCYAN << " [options]" << CRESET << std::endl;
		std::cout << CPURPLE << "Arguments:" << std::endl;
		std::cout << CGREEN << "  -C, --config <filename>\tLoad the scene from a JSON file" << CRESET << std::endl;
		std::cout << CPURPLE << "Options:" << std::endl;
		std::cout << CCYAN << "  -h, --help\t\t\tShow this help message" << CRESET << std::endl;
		std::cout << CCYAN << "  -S, --save <filename>\t\tSave the image to a PNG file" << CRESET << std::endl;
		std::cout << CCYAN << "  -T, --threads <number>\tUse a specific number of threads for rendering (default is 4)" << CRESET << std::endl;
		std::cout << CCYAN << "  -O, --octree\t\t\tEnable the use of an octree for faster high-density mesh rendering" << CRESET << std::endl;
		std::cout << CCYAN << "  --no-display\t\t\tDo not open a window to display the image" << CRESET << std::endl;
	}

	bool handleSAVE(int &i, const char **argv, int argc, std::string &filename)
	{
		i++;
		if (i < argc)
		{
			filename = argv[i];
			if (!my3d::isValidExtension(filename, ".png"))
			{
				std::cout << CRED << "Error: The provided filename does not have a .png or .PNG extension." << CRESET << std::endl;
				return false;
			}
			return true;
		}
		else
		{
			std::cout << CRED << "Error: missing filename after " << argv[i - 1] << CRESET << std::endl;
			return false;
		}
	}

	bool handleCONFIG(int &i, const char **argv, int argc, std::string &filename)
	{
		i++;
		if (i < argc)
		{
			filename = argv[i];
			if (!my3d::isValidExtension(filename, ".json"))
			{
				std::cout << CRED << "Error: The provided filename does not have a .json or .JSON extension." << CRESET << std::endl;
				return false;
			}
			return true;
		}
		else
		{
			std::cout << CRED << "Error: missing filename after " << argv[i - 1] << CRESET << std::endl;
			return false;
		}
	}

	bool handleTHREADS(int &i, const char **argv, int argc, int &threads)
	{
		i++;
		if (i < argc)
		{
			threads = std::stoi(argv[i]);
			if (threads <= 0)
			{
				std::cout << CRED << "Error: The number of threads must be greater than 0." << CRESET << std::endl;
				return false;
			}
			return true;
		}
		else
		{
			std::cout << CRED << "Error: missing number of threads after " << argv[i - 1] << CRESET << std::endl;
			return false;
		}
	}

	int argumentParser(int argc, char **argv, std::string &configFilename, std::string &saveFilename, int &threads, bool &octree, bool &display)
	{
		std::map<std::string, ArgumentType, std::less<>> argumentMap = {
			{"-h", ArgumentType::HELP},
			{"--help", ArgumentType::HELP},
			{"-S", ArgumentType::SAVE},
			{"--save", ArgumentType::SAVE},
			{"-C", ArgumentType::CONFIG},
			{"--config", ArgumentType::CONFIG},
			{"-T", ArgumentType::THREADS},
			{"--threads", ArgumentType::THREADS},
			{"--octree", ArgumentType::OCTREE},
			{"-O", ArgumentType::OCTREE},
			{"--no-display", ArgumentType::DISPLAY}};

		int i = 1;
		while (i < argc)
		{
			switch (std::string arg = argv[i]; argumentMap.count(arg) ? argumentMap[arg] : ArgumentType::UNKNOWN)
			{
			case ArgumentType::HELP:
				my3d::displayHelp(argv[0]);
				return 1;

			case ArgumentType::SAVE:
				if (!my3d::handleSAVE(i, (const char **)argv, argc, saveFilename))
					return 1;
				break;

			case ArgumentType::CONFIG:
				if (!my3d::handleCONFIG(i, (const char **)argv, argc, configFilename))
					return 1;
				break;

			case ArgumentType::THREADS:
				if (!my3d::handleTHREADS(i, (const char **)argv, argc, threads))
					return 1;
				break;

			case ArgumentType::OCTREE:
				octree = true;
				break;

			case ArgumentType::DISPLAY:
				display = false;
				break;

			default:
				std::cout << CRED << "Error: Unknown argument " << arg << CRESET << std::endl;
				std::cout << CYELLOW << "Try '" << argv[0] << " --help' for more information" << CRESET << std::endl;
				return 1;
			}
			i++;
		}

		if (configFilename.empty())
		{
			std::cout << CRED << "Error: No config file provided" << CRESET << std::endl;
			std::cout << CYELLOW << "Try '" << argv[0] << " --help' for more information" << CRESET << std::endl;
			return 1;
		}

		// COUT a recap of every parameters
		std::cout << CBLUE << "3D Engine Rendering Parameters:" << CRESET << std::endl;
		std::cout << CBLUE << "\t[x] CONFIG GIVEN" << CRESET << std::endl;
		std::cout << CBLUE << "\t\tConfig file: " << configFilename << CRESET << std::endl;
		std::cout << CBLUE << "\t[" << (saveFilename.empty() ? " " : "x") << "] SAVING IMAGE" << CRESET << std::endl;
		if (!saveFilename.empty())
			std::cout << CBLUE << "\t\tSave file: " << saveFilename << CRESET << std::endl;
		std::cout << CBLUE << "\t[" << (threads > 1 ? "x" : " ") << "] MULTITHREADING" << CRESET << std::endl;
		if (threads > 1)
			std::cout << CBLUE << "\t\tThreads: " << threads << CRESET << std::endl;
		std::cout << CBLUE << "\t[" << (octree ? "x" : " ") << "] OCTREE" << CRESET << std::endl;
		std::cout << CBLUE << "\t[" << (display ? "x" : " ") << "] DISPLAY" << CRESET << std::endl
				  << std::endl;

		return 0;
	}

	std::vector<myVector3> generateRingRays(const myVector3 &direction, int rays, double deviationAngle)
	{
		std::vector<myVector3> directions;
		myVector3 perpendicularAxis1 = direction.findPerpendicular();
		myVector3 perpendicularAxis2 = direction ^ perpendicularAxis1;

		for (int i = 0; i < rays; ++i)
		{
			double angle = 2 * M_PI * i / rays;
			myVector3 rotatedRay = direction.rotateVector(perpendicularAxis1, cos(angle) * deviationAngle);
			rotatedRay = rotatedRay.rotateVector(perpendicularAxis2, sin(angle) * deviationAngle);
			rotatedRay.normalize();
			directions.push_back(rotatedRay);
		}

		return directions;
	}

	std::vector<myVector3> ringDirection(const myVector3 &direction)
	{
		std::vector<myVector3> directions;
		directions.push_back(direction);

		int points = 1;

		for (int i = 0; i < 9; i++)
		{
			points += 2;
			std::vector<myVector3> ring = generateRingRays(direction, points, 0.02 * (i + 1));
			directions.insert(directions.end(), ring.begin(), ring.end());
		}

		return directions;
	}

	std::vector<myVector3> randomizeDirection(const myVector3 &direction)
	{
		std::vector<myVector3> directions;

		directions.push_back(direction);

		for (int i = 0; i < 60; i++)
		{
			myVector3 newDirection = direction;
			newDirection.x += ((double)rand() / RAND_MAX - 0.5) * 0.5;
			newDirection.y += ((double)rand() / RAND_MAX - 0.5) * 0.1;
			newDirection.z += ((double)rand() / RAND_MAX - 0.5) * 0.1;
			newDirection.normalize();
			directions.push_back(newDirection);
		}

		return directions;
	}

	void renderingLog(int &state, SYSTEM_CLOCK_TIME_POINT &lastUpdate)
	{
		if (std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - lastUpdate).count() > 100)
		{
			std::cout << CPURPLE;

			switch (state)
			{
			case 0:
				std::cout << "\rRendering [-]" << CRESET << std::flush;
				state = 1;
				break;
			case 1:
				std::cout << "\rRendering [\\]" << CRESET << std::flush;
				state = 2;
				break;
			case 2:
				std::cout << "\rRendering [|]" << CRESET << std::flush;
				state = 3;
				break;
			case 3:
				std::cout << "\rRendering [/]" << CRESET << std::flush;
				state = 0;
				break;
			}

			lastUpdate = std::chrono::steady_clock::now();
		}
	}

	// std::vector<myVector3> randomizeDirection(const myVector3& direction) {
	//     std::vector<myVector3> directions;

	//     for (int i = 0; i < 30; i++) {
	//         myVector3 newDirection;

	//         double theta = DPI * ((double)rand() / (double)RAND_MAX);
	//         double phi = acos(2 * ((double)rand() / (double)RAND_MAX) - 1.0);

	//         newDirection.x = cos(theta)*sin(phi);
	//         newDirection.y = sin(theta)*sin(phi);
	//         newDirection.z = cos(phi);

	//         newDirection.normalize();

	//         directions.push_back(direction + (0.2 * newDirection));
	//     }

	//     return directions;
	// }
}
