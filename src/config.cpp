#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include <nlohmann/json.hpp>

#include "config.hpp"

namespace config
{
	nlohmann::json parseJSON(std::string_view const &filename)
	{
		std::ifstream file(filename.data());
		if (!file)
		{
			std::cout << CRED << "Error: Could not open file " << filename << CRESET << std::endl;
			return nlohmann::json();
		}

		nlohmann::json j;
		file >> j;
		return j;
	}

	int loadLights(const nlohmann::json &j, std::vector<std::unique_ptr<myLight>> &lights)
	{
		if (!j.contains("lights"))
		{
			std::cout << CRED << "Error: No lights found in config file, at least one light is required" << CRESET << std::endl;
			return 1;
		}

		for (const auto &light : j["lights"])
		{
			if (!light.contains("type") || !light.contains("color") || !light.contains("intensity"))
			{
				std::cout << CYELLOW << "Warning: Skipping light with missing fields" << CRESET << std::endl;
				continue;
			}

			if (light["type"] == "AmbientLight")
			{
				lights.push_back(std::make_unique<myAmbientLight>(
					myColor(light["color"].get<std::vector<int>>()), light["intensity"].get<double>()));

				std::cout << CGREEN << "[" << lights.size() << "] Loaded AmbientLight" << CRESET << std::endl;
			}
			else if (light["type"] == "DirectionalLight")
			{
				if (!light.contains("direction"))
				{
					std::cout << CYELLOW << "Warning: Skipping DirectionalLight with missing fields" << CRESET << std::endl;
					continue;
				}

				lights.push_back(std::make_unique<myDirectionalLight>(
					myColor(light["color"].get<std::vector<int>>()),
					myVector3(light["direction"].get<std::vector<double>>()),
					light["intensity"].get<double>()));

				std::cout << CGREEN << "[" << lights.size() << "] Loaded DirectionalLight" << CRESET << std::endl;
			}
			else
			{
				std::cout << CYELLOW << "Warning: Unknown light type, skipping" << CRESET << std::endl;
				continue;
			}
		}

		if (lights.empty())
		{
			std::cout << CRED << "Error: No lights found in config file, at least one light is required" << CRESET << std::endl;
			return 1;
		}

		return 0;
	}

	int loadShapes(const nlohmann::json &j, std::vector<std::unique_ptr<myShape>> &shapes, bool octree)
	{
		if (!j.contains("shapes"))
		{
			std::cout << CRED << "Error: No shapes found in config file, at least one shape is required" << CRESET << std::endl;
			return 1;
		}

		int latestStatus = 0;

		for (const auto &shape : j["shapes"])
		{
			if (!shape.contains("type"))
			{
				std::cout << CYELLOW << "Warning: Skipping shape with missing type" << CRESET << std::endl;
				continue;
			}

			if (shape["type"] == "Sphere")
			{
				latestStatus = loadSphere(shape, shapes);

				if (latestStatus == 1)
					return 1;
				else if (latestStatus == 2)
					continue;

				std::cout << CGREEN << "[" << shapes.size() << "] Loaded Sphere" << CRESET << std::endl;
			}
			else if (shape["type"] == "Parallelogram")
			{
				latestStatus = loadParallelogram(shape, shapes);

				if (latestStatus == 1)
					return 1;
				else if (latestStatus == 2)
					continue;

				std::cout << CGREEN << "[" << shapes.size() << "] Loaded Parallelogram" << CRESET << std::endl;
			}
			else if (shape["type"] == "Triangle")
			{
				latestStatus = loadTriangle(shape, shapes);

				if (latestStatus == 1)
					return 1;
				else if (latestStatus == 2)
					continue;

				std::cout << CGREEN << "[" << shapes.size() << "] Loaded Triangle" << CRESET << std::endl;
			}
			else if (shape["type"] == "Obj")
			{
				latestStatus = loadMesh(shape, shapes, octree);

				if (latestStatus == 1)
					return 1;
				else if (latestStatus == 2)
					continue;

				std::cout << CGREEN << "[" << shapes.size() << "] Loaded Mesh" << CRESET << std::endl;
			}
			else
			{
				std::cout << CYELLOW << "Warning: Unknown shape type, skipping" << CRESET << std::endl;
				continue;
			}
		}

		if (shapes.empty())
		{
			std::cout << CRED << "Error: No shapes found in config file, at least one shape is required" << CRESET << std::endl;
			return 1;
		}

		return 0;
	}

	int loadSphere(const nlohmann::json &shape, std::vector<std::unique_ptr<myShape>> &shapes)
	{
		if (!shape.contains("center") || !shape.contains("radius") || (!shape.contains("color") && !shape.contains("texture")))
		{
			std::cout << CYELLOW << "Warning: Skipping sphere with missing fields" << CRESET << std::endl;
			return 2;
		}

		std::unique_ptr<mySphere> s;
		if (shape.contains("color"))
		{
			s = std::make_unique<mySphere>(
				myVector3(shape["center"].get<std::vector<double>>()),
				shape["radius"].get<double>(),
				myColor(shape["color"].get<std::vector<int>>()),
				shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
				shape.contains("fresnel") ? shape["fresnel"].get<double>() : 1.0,
				shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
				shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0);
		}
		else if (shape.contains("texture"))
		{
			s = std::make_unique<mySphere>(
				myVector3(shape["center"].get<std::vector<double>>()),
				shape["radius"].get<double>(),
				shape["texture"].get<std::string>(),
				shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
				shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
				shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
				shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0);

			if (s->hasTextureError())
				return 1;
		}
		else
		{
			std::cout << CYELLOW << "Warning: Skipping sphere with missing fields" << CRESET << std::endl;
		}

		if (shape.contains("bumpMap"))
		{
			if (s->setBumpMap(shape["bumpMap"].get<std::string>()) == false)
				return 1;
		}
		shapes.push_back(std::move(s));

		return 0;
	}

	int loadParallelogram(const nlohmann::json &shape, std::vector<std::unique_ptr<myShape>> &shapes)
	{
		if (!shape.contains("A") || !shape.contains("B") || !shape.contains("C") || (!shape.contains("color") && !shape.contains("texture")))
		{
			std::cout << CYELLOW << "Warning: Skipping parallelogram with missing fields" << CRESET << std::endl;
			return 2;
		}

		std::unique_ptr<myParallelogram> p;
		if (shape.contains("color"))
		{
			p = std::make_unique<myParallelogram>(
				myVector3(shape["A"].get<std::vector<double>>()),
				myVector3(shape["B"].get<std::vector<double>>()),
				myVector3(shape["C"].get<std::vector<double>>()),
				myColor(shape["color"].get<std::vector<int>>()),
				shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
				shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
				shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
				shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0);
		}
		else if (shape.contains("texture"))
		{
			p = std::make_unique<myParallelogram>(
				myVector3(shape["A"].get<std::vector<double>>()),
				myVector3(shape["B"].get<std::vector<double>>()),
				myVector3(shape["C"].get<std::vector<double>>()),
				shape["texture"].get<std::string>(),
				shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
				shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
				shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
				shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0);

			if (p->hasTextureError())
				return 1;
		}
		else
		{
			std::cout << CYELLOW << "Warning: Skipping parallelogram with missing fields" << CRESET << std::endl;
		}

		if (shape.contains("bumpMap"))
		{
			if (p->setBumpMap(shape["bumpMap"].get<std::string>()) == false)
				return 1;
		}
		shapes.push_back(std::move(p));

		return 0;
	}

	int loadTriangle(const nlohmann::json &shape, std::vector<std::unique_ptr<myShape>> &shapes)
	{
		if (!shape.contains("A") || !shape.contains("B") || !shape.contains("C") || (!shape.contains("color") && !shape.contains("texture")))
		{
			std::cout << CYELLOW << "Warning: Skipping triangle with missing fields" << CRESET << std::endl;
			return 2;
		}

		std::unique_ptr<myTriangle> t;
		if (shape.contains("color"))
		{
			t = std::make_unique<myTriangle>(
				myVector3(shape["A"].get<std::vector<double>>()),
				myVector3(shape["B"].get<std::vector<double>>()),
				myVector3(shape["C"].get<std::vector<double>>()),
				myColor(shape["color"].get<std::vector<int>>()),
				shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
				shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
				shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
				shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0);
		}
		else if (shape.contains("texture"))
		{
			t = std::make_unique<myTriangle>(
				myVector3(shape["A"].get<std::vector<double>>()),
				myVector3(shape["B"].get<std::vector<double>>()),
				myVector3(shape["C"].get<std::vector<double>>()),
				shape["texture"].get<std::string>(),
				shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
				shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
				shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
				shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0);

			if (t->hasTextureError())
				return 1;
		}
		else
		{
			std::cout << CYELLOW << "Warning: Skipping triangle with missing fields" << CRESET << std::endl;
		}

		if (shape.contains("bumpMap"))
		{
			if (t->setBumpMap(shape["bumpMap"].get<std::string>()) == false)
				return 1;
		}
		shapes.push_back(std::move(t));

		return 0;
	}

	int loadMesh(const nlohmann::json &shape, std::vector<std::unique_ptr<myShape>> &shapes, bool octree)
	{
		if (!shape.contains("obj") || !shape.contains("position") || !shape.contains("color"))
		{
			std::cout << CYELLOW << "Warning: Skipping mesh with missing fields" << CRESET << std::endl;
			return 2;
		}

		std::string filename = shape["obj"].get<std::string>();

		std::vector<myVector3> vertices;
		std::vector<std::vector<int>> faces;

		std::ifstream file(filename);
		std::string line;

		if (!file.is_open())
		{
			std::cout << CRED << "Error: Could not open object file " << filename << CRESET << std::endl;
			return 1;
		}

		while (getline(file, line))
		{
			std::istringstream iss(line);
			std::string identifier;
			iss >> identifier;

			if (identifier == "v")
			{
				double x, y, z;
				iss >> x >> y >> z;
				vertices.push_back(myVector3(x, y, z));
			}
			else if (identifier == "f")
			{
				std::vector<int> face;
				std::string vertIndex;
				while (iss >> vertIndex)
				{
					size_t slashPop = vertIndex.find("/");
					if (slashPop != std::string::npos)
					{
						vertIndex = vertIndex.substr(0, slashPop);
					}
					face.push_back(std::stoi(vertIndex));
				}
				if (face.size() == 3)
				{
					faces.push_back(face);
				}
				else
				{
					for (size_t i = 1; i < face.size() - 1; i++)
					{
						faces.push_back({face[0], face[i], face[i + 1]});
					}
				}
			}
		}

		file.close();

		myVector3 pos(shape["position"].get<std::vector<double>>());

		double scale = 1.0;
		myVector3 rot = myVector3::ZERO;

		if (shape.contains("scale"))
			scale = shape["scale"].get<double>();
		if (shape.contains("rotation"))
			rot = myVector3(shape["rotation"].get<std::vector<double>>());

		myVector3 testRotX = myVector3(rot.x, 0, 0);
		myVector3 testRotY = myVector3(0, rot.y, 0);
		myVector3 testRotZ = myVector3(0, 0, rot.z);

		for (auto &vertex : vertices)
		{
			vertex = vertex.rotateVector(rot);
			vertex = vertex * scale + pos;
		}

		std::unique_ptr<myMesh> m = std::make_unique<myMesh>(
			myColor(shape["color"].get<std::vector<int>>()),
			shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
			shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
			shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
			shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0);

		for (const auto &face : faces)
		{
			std::unique_ptr<myTriangle> t = std::make_unique<myTriangle>(
				vertices[face[0] - 1],
				vertices[face[1] - 1],
				vertices[face[2] - 1],
				myColor(shape["color"].get<std::vector<int>>()),
				shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
				shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
				shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
				shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0);

			m->addTriangle(std::move(t));
		}

		m->computeBoundingBox(0, octree);

		shapes.push_back(std::move(m));

		return 0;
	}

	int loadConfig(std::string_view const &filename, std::vector<std::unique_ptr<myShape>> &shapes, std::vector<std::unique_ptr<myLight>> &lights, bool octree)
	{
		if (!std::filesystem::exists(filename))
		{
			std::cout << CRED << "Error: Could not find file " << filename << CRESET << std::endl;
			return 1;
		}

		nlohmann::json j = parseJSON(filename);

		if (j.empty())
			return 1;

		if (loadLights(j, lights) == 1 || loadShapes(j, shapes, octree) == 1)
			return 1;

		return 0;
	}
}