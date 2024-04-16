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
#include "myAmbientLight.hpp"
#include "myDirectionalLight.hpp"

namespace config {
    void loadConfig(std::string_view const& filename, std::vector<std::unique_ptr<myShape>>& shapes, std::vector<std::unique_ptr<myLight>>& lights);
    nlohmann::json loadJSON(std::string_view const& filename);
    void loadLights(nlohmann::json const& config, std::vector<std::unique_ptr<myLight>>& lights);
    void loadShapes(nlohmann::json const& config, std::vector<std::unique_ptr<myShape>>& shapes);
    void loadSphere(nlohmann::json const& config, std::vector<std::unique_ptr<myShape>>& shapes);
    void loadParallelogram(nlohmann::json const& config, std::vector<std::unique_ptr<myShape>>& shapes);
    void loadTriangle(nlohmann::json const& config, std::vector<std::unique_ptr<myShape>>& shapes);
    void loadObj(nlohmann::json const& config, std::vector<std::unique_ptr<myShape>>& shapes);
}