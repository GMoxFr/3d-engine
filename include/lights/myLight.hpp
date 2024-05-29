#pragma once

#include "myColor.hpp"

enum class myLightType
{
    AMBIENT,
    DIRECTIONAL
};

class myLight
{
private:
    myColor color;
    myLightType type;

protected:
    const myColor &getColor() const { return color; }
    void setColor(myColor const &clr) { color = clr; }

public:
    explicit myLight(myColor const &clr, myLightType t) : color(clr),
                                                          type(t){};

    virtual ~myLight() = default;

    virtual myColor applyLighting(myVector3 pos, myVector3 normal, myColor const &workingColor, double diffuse) = 0;

    const myLightType &getType() const { return type; }
    virtual myVector3 getDirection() const = 0;
};