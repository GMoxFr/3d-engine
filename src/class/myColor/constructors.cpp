#include "myColor.hpp"

myColor::myColor() : myColor(0.0, 0.0, 0.0, 0.0) {}

// Constructor with RGBA values
myColor::myColor(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a) : r(static_cast<double>(r) / 255.0),
																   g(static_cast<double>(g) / 255.0),
																   b(static_cast<double>(b) / 255.0),
																   a(static_cast<double>(a) / 255.0) {}

myColor::myColor(int r, int g, int b, int a) : myColor(static_cast<u_int8_t>(r), static_cast<u_int8_t>(g), static_cast<u_int8_t>(b), static_cast<u_int8_t>(a)) {}

// Copy constructor from sf::Color
myColor::myColor(const sf::Color &c) : myColor(c.r, c.g, c.b, c.a) {}

// Constructor with RGBA values as doubles
myColor::myColor(double r, double g, double b, double a) : r(my3d::clamp(r)), g(my3d::clamp(g)), b(my3d::clamp(b)), a(my3d::clamp(a)) {}

// Constructor with a vector of 4 integers
myColor::myColor(const std::vector<int> &components)
{
	if (components.size() < 3)
	{
		throw InvalidColorException();
	}

	r = static_cast<double>(components[0]) / 255.0;
	g = static_cast<double>(components[1]) / 255.0;
	b = static_cast<double>(components[2]) / 255.0;
	a = components.size() > 3 ? static_cast<double>(components[3]) / 255.0 : 1.0;
}