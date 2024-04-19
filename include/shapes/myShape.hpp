#pragma once

#include "myImage.hpp"
#include "myColor.hpp"
#include "myTexture.hpp"
#include "myLight.hpp"

class myImage;

class myShape {
    protected:
        myColor color;

        bool hasTexture = false;
        std::unique_ptr<myTexture> texture;

        bool hasBumpMap = false;
        std::unique_ptr<myTexture> bumpMap;

        double diffuse;

        double fresnel;
        double reflection;
        double refraction;

    protected:
        void setColor(myColor const& clr) { color = clr; }

        const myTexture& getTexture() const { return *texture; }

        const myTexture& getBumpMap() const { return *bumpMap; }

        bool getHasTexture() const { return hasTexture; }
        bool getHasBumpMap() const { return hasBumpMap; }

        void setDiffuse(double d) { diffuse = d; }

        void setFresnel(double f) { fresnel = f; }

        void setReflection(double r) { reflection = r; }

        void setRefraction(double r) { refraction = r; }

    public:
        myShape(myColor const& clr, double diffuse = 1.0, double fresnel = 1.0, double reflection = 0.0, double refraction = 0.0) :
            color(clr),
            hasTexture(false),
            diffuse(diffuse),
            fresnel(fresnel),
            reflection(reflection),
            refraction(refraction)
        {};

        myShape(std::string const& texture, double diffuse = 1.0, double fresnel = 1.0, double reflection = 0.0, double refraction = 0.0) :
            hasTexture(true),
            diffuse(diffuse),
            fresnel(fresnel),
            reflection(reflection),
            refraction(refraction)
        {
            this->texture = std::make_unique<myTexture>(texture);
        };

        virtual ~myShape() = default;

        void setTexture(std::string const& filename) {
            hasTexture = true;
            texture = std::make_unique<myTexture>(filename);
        }

        void removeTexture() {
            hasTexture = false;
            texture.reset();
        }

        void setBumpMap(std::string const& filename) {
            hasBumpMap = true;
            bumpMap = std::make_unique<myTexture>(filename);
        }

        void removeBumpMap() {
            hasBumpMap = false;
            bumpMap.reset();
        }

        const myColor& getColor() const { return color; }
        double getDiffuse() const { return diffuse; }
        double getFresnel() const { return fresnel; }
        double getReflection() const { return reflection; }
        double getRefraction() const { return refraction; }

        myColor applyLighting(myVector3 pos, myVector3 normal, myColor const& workingColor, std::vector<std::unique_ptr<myLight>> const& lights, std::vector<std::unique_ptr<myShape>> const& shapes) const {
            myColor newColor(0, 0, 0);

            for (std::unique_ptr<myLight> const& light : lights) {
                if (light->getType() != myLightType::DIRECTIONAL) {
                    newColor += light->applyLighting(pos, normal, workingColor, diffuse);
                    continue;
                }

                double lightIntensity = 1.0;
                std::vector<myVector3> directions = my3d::ringDirection(-light->getDirection());

                for(myVector3 const& dir : directions) {
                    bool blocked = false;
                    for (std::unique_ptr<myShape> const& shape : shapes) {
                        if (shape.get() == this) continue;

                        if (shape->intersect(pos, dir)) {
                            blocked = true;
                            break;
                        }
                    }
                    if (blocked)
                        lightIntensity -= 1.0 / static_cast<double>(directions.size());
                }

                newColor += (light->applyLighting(pos, normal, workingColor, diffuse) * lightIntensity);
            }

            return newColor;
        }

        virtual void draw(myImage& I, std::vector<std::unique_ptr<myLight>> const& L) = 0;
        virtual bool intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color, double &u, double &v) = 0;
        virtual bool intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color) = 0;
        virtual bool intersect(myVector3 const& origin, myVector3 const& direction) = 0;
        virtual double intersectDistance(myVector3 const& origin, myVector3 const& direction) = 0;
};