#include <algorithm>
#include <thread>
#include <chrono>
#include <fstream>
#include <nlohmann/json.hpp>

#include "config.hpp"

namespace config {
    
    nlohmann::json parseJSON(std::string_view const& filename) {
        std::ifstream file(filename.data());
        if (!file) {
            throw CouldNotOpenFileException();
        }

        nlohmann::json j;
        file >> j;
        return j;
    }

    void loadLights(const nlohmann::json& j, std::vector<std::unique_ptr<myLight>>& lights) {
        for (const auto& light : j["lights"]) {
            if (light["type"] == "AmbientLight") {
                lights.push_back(std::make_unique<myAmbientLight>(
                    myColor(light["color"].get<std::vector<int>>()), light["intensity"].get<double>()
                ));
            } else if (light["type"] == "DirectionalLight") {
                lights.push_back(std::make_unique<myDirectionalLight>(
                    myColor(light["color"].get<std::vector<int>>()),
                    myVector3(light["direction"].get<std::vector<double>>()),
                    light["intensity"].get<double>()
                ));
            }
        }
    }

    void loadShapes(const nlohmann::json& j, std::vector<std::unique_ptr<myShape>>& shapes) {
        for (const auto& shape : j["shapes"]) {
            if (shape["type"] == "Sphere") {
                loadSphere(shape, shapes);
            } else if (shape["type"] == "Parallelogram") {
                loadParallelogram(shape, shapes);
            } else if (shape["type"] == "Triangle") {
                loadTriangle(shape, shapes);
            }
        }
    }

    void loadSphere(const nlohmann::json& shape, std::vector<std::unique_ptr<myShape>>& shapes) {
        std::unique_ptr<mySphere> s;
        if (shape.contains("color")) {
            s = std::make_unique<mySphere>(
                myVector3(shape["center"].get<std::vector<double>>()),
                shape["radius"].get<double>(),
                myColor(shape["color"].get<std::vector<int>>()),
                shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
                shape.contains("fresnel") ? shape["fresnel"].get<double>() : 1.0,
                shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
                shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0
            );
        } else if (shape.contains("texture")) {
            s = std::make_unique<mySphere>(
                myVector3(shape["center"].get<std::vector<double>>()),
                shape["radius"].get<double>(),
                shape["texture"].get<std::string>(),
                shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
                shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
                shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
                shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0
            );
        } else {
            throw InvalidShapeException();
        }

        if (shape.contains("bumpMap")) {
            s->setBumpMap(shape["bumpMap"].get<std::string>());
        }
        shapes.push_back(std::move(s));
    }

    void loadParallelogram(const nlohmann::json& shape, std::vector<std::unique_ptr<myShape>>& shapes) {
        std::unique_ptr<myParallelogram> p;
        if (shape.contains("color")) {
            p = std::make_unique<myParallelogram>(
                myVector3(shape["A"].get<std::vector<double>>()),
                myVector3(shape["B"].get<std::vector<double>>()),
                myVector3(shape["C"].get<std::vector<double>>()),
                myColor(shape["color"].get<std::vector<int>>()),
                shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
                shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
                shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
                shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0
            );
        } else if (shape.contains("texture")) {
            p = std::make_unique<myParallelogram>(
                myVector3(shape["A"].get<std::vector<double>>()),
                myVector3(shape["B"].get<std::vector<double>>()),
                myVector3(shape["C"].get<std::vector<double>>()),
                shape["texture"].get<std::string>(),
                shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
                shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
                shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
                shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0
            );
        } else {
            throw InvalidShapeException();
        }

        if (shape.contains("bumpMap")) {
            p->setBumpMap(shape["bumpMap"].get<std::string>());
        }
        shapes.push_back(std::move(p));
    }

    void loadTriangle(const nlohmann::json& shape, std::vector<std::unique_ptr<myShape>>& shapes) {
        std::unique_ptr<myTriangle> t;
        if (shape.contains("color")) {
            t = std::make_unique<myTriangle>(
                myVector3(shape["A"].get<std::vector<double>>()),
                myVector3(shape["B"].get<std::vector<double>>()),
                myVector3(shape["C"].get<std::vector<double>>()),
                myColor(shape["color"].get<std::vector<int>>()),
                shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
                shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
                shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
                shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0
            );
        } else if (shape.contains("texture")) {
            t = std::make_unique<myTriangle>(
                myVector3(shape["A"].get<std::vector<double>>()),
                myVector3(shape["B"].get<std::vector<double>>()),
                myVector3(shape["C"].get<std::vector<double>>()),
                shape["texture"].get<std::string>(),
                shape.contains("diffuse") ? shape["diffuse"].get<double>() : 1.0,
                shape.contains("fresnel") ? shape["fresnel"].get<double>() : 0.0,
                shape.contains("reflection") ? shape["reflection"].get<double>() : 0.0,
                shape.contains("refraction") ? shape["refraction"].get<double>() : 0.0
            );
        } else {
            throw InvalidShapeException();
        }

        if (shape.contains("bumpMap")) {
            t->setBumpMap(shape["bumpMap"].get<std::string>());
        }
        shapes.push_back(std::move(t));
    }

    void loadConfig(std::string_view const& filename, std::vector<std::unique_ptr<myShape>>& shapes, std::vector<std::unique_ptr<myLight>>& lights) {
        nlohmann::json j = parseJSON(filename);

        loadLights(j, lights);
        loadShapes(j, shapes);
    }
}