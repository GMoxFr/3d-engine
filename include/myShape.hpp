#pragma once

#include "myImage.hpp"
#include "myColor.hpp"
#include "myTexture.hpp"
#include "myLight.hpp"

class myImage;

class myShape {
    private:
        myColor color;

        bool hasTexture;
        std::unique_ptr<myTexture> texture;

        bool hasBumpMap = false;
        std::unique_ptr<myTexture> bumpMap;

        double diffuse;

    protected:
        const myColor& getColor() const { return color; }
        void setColor(myColor const& clr) { color = clr; }

        const myTexture& getTexture() const { return *texture; }

        const myTexture& getBumpMap() const { return *bumpMap; }

        bool getHasTexture() const { return hasTexture; }
        bool getHasBumpMap() const { return hasBumpMap; }

        double getDiffuse() const { return diffuse; }
        void setDiffuse(double d) { diffuse = d; }

    public:
        myShape(myColor const& clr, double diffuse = 1.0) :
            color(clr),
            hasTexture(false),
            diffuse(diffuse)
        {};

        myShape(std::string const& texture, double diffuse = 1.0) :
            hasTexture(true),
            diffuse(diffuse)
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

        myColor applyLighting(myVector3 pos, myVector3 normal, myColor const& workingColor, std::vector<myLight*> const& lights) {
            myColor newColor(0, 0, 0);

            for (myLight* light : lights) {
                newColor += light->applyLighting(pos, normal, workingColor, diffuse);
            }

            return newColor;
        }

        virtual void draw(myImage& I, std::vector<myLight *> const& L) = 0;
        virtual bool intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color, double &u, double &v) = 0;
};