#include "myColor.hpp"

myColor::myColor() : myColor(0, 0, 0, 0) { }

// Constructor with RGBA values
myColor::myColor(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a) : r(r), g(g), b(b), a(a) { }	
myColor::myColor(int r, int g, int b, int a) : myColor(static_cast<u_int8_t>(r), static_cast<u_int8_t>(g), static_cast<u_int8_t>(b), static_cast<u_int8_t>(a)) { }

// Copy constructor
myColor::myColor(const myColor& c) : myColor(c.r, c.g, c.b, c.a) { }

// Copy constructor from sf::Color
myColor::myColor(const sf::Color& c) : myColor(c.r, c.g, c.b, c.a) { }

// Constructor with RGBA values as doubles
myColor::myColor(double r, double g, double b, double a) : myColor(
    static_cast<u_int8_t>(round(my3d::clamp(r) * 255)), 
    static_cast<u_int8_t>(round(my3d::clamp(g) * 255)), 
    static_cast<u_int8_t>(round(my3d::clamp(b) * 255)), 
    static_cast<u_int8_t>(round(my3d::clamp(a) * 255))
    ) { }

// Destructor
myColor::~myColor() { }