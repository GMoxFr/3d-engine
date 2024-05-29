#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <string_view>
#include <fstream>
#include <nlohmann/json.hpp>

#include "my3d.hpp"
#include "myShape.hpp"
#include "myLight.hpp"
#include "myVector3.hpp"
#include "myColor.hpp"
#include "myTexture.hpp"
#include "mySphere.hpp"
#include "myParallelogram.hpp"
#include "myTriangle.hpp"
#include "myMesh.hpp"
#include "myAmbientLight.hpp"
#include "myDirectionalLight.hpp"

namespace config
{
    int loadConfig(std::string_view const &filename, std::vector<std::unique_ptr<myShape>> &shapes, std::vector<std::unique_ptr<myLight>> &lights, bool octree);
    nlohmann::json loadJSON(std::string_view const &filename);
    int loadLights(nlohmann::json const &config, std::vector<std::unique_ptr<myLight>> &lights);
    int loadShapes(nlohmann::json const &config, std::vector<std::unique_ptr<myShape>> &shapes, bool octree);
    int loadSphere(nlohmann::json const &config, std::vector<std::unique_ptr<myShape>> &shapes);
    int loadParallelogram(nlohmann::json const &config, std::vector<std::unique_ptr<myShape>> &shapes);
    int loadTriangle(nlohmann::json const &config, std::vector<std::unique_ptr<myShape>> &shapes);
    int loadMesh(nlohmann::json const &config, std::vector<std::unique_ptr<myShape>> &shapes, bool octree);
}