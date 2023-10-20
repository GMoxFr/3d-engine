#pragma once

#include "myImage.hpp"

class myShape {
    public:
        virtual ~myShape() {};

        virtual void draw(myImage& I) = 0;
};