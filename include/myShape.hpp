#pragma once

#include "myImage.hpp"
#include "myColor.hpp"
#include "myTexture.hpp"
#include "myLight.hpp"

class myImage;

class myShape {
    protected:
        myColor color;

        bool hasTexture;
        myTexture *texture;

        bool hasBumpMap = false;
        myTexture *bumpMap;

        double diffuse;

    public:
        myShape(myColor clr, double diffuse = 1.0) :
            color(clr),
            hasTexture(false),
            diffuse(diffuse)
        {};

        myShape(std::string texture, double diffuse = 1.0) :
            hasTexture(true),
            diffuse(diffuse)
        {
            this->texture = new myTexture(texture);
        };

        virtual ~myShape() {};

        void setBumpMap(std::string filename) {
            hasBumpMap = true;
            bumpMap = new myTexture(filename);
        }

        myColor applyLighting(myVector3 pos, myVector3 normal, myColor const& workingColor, std::vector<myLight*> const& lights) {
            myColor newColor(0, 0, 0);

            for (myLight* light : lights) {
                newColor += light->applyLighting(pos, normal, workingColor, diffuse);
            }

            return newColor;
        }

        virtual void draw(myImage& I, std::vector<myLight *> L) = 0;
        virtual bool intersect(myVector3 const& origin, myVector3 const& direction, myVector3& intersection, myVector3& normal, myColor& color, double &u, double &v) = 0;
};