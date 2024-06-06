#pragma once

#include "myVector3.hpp"
#include "myLight.hpp"

class myAmbientLight : public myLight
{
private:
	double intensity;

public:
	myAmbientLight(myColor const &clr, double intensity = 1.0, myLightType t = myLightType::AMBIENT) : myLight(clr, t),
																									   intensity(intensity) {};

	myColor applyLighting(myVector3 pos, myVector3 normal, myColor const &workingColor, double diffuse) override
	{
		(void)pos;
		(void)normal;
		(void)diffuse;
		return (getColor() * intensity) * workingColor;
	};

	myVector3 getDirection() const override { return myVector3(0, 0, 0); }
};