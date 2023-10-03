#include "3dengine.hpp"

// Default constructor
myColor::myColor() {
    r = 0;
    g = 0;
    b = 0;
    a = 255;
}

// Constructor with RGB values
myColor::myColor(u_int8_t r, u_int8_t g, u_int8_t b) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = 255;
}

// Constructor with RGBA values
myColor::myColor(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

// Constructor with RGB values as int
myColor::myColor(int r, int g, int b) {
    this->r = (u_int8_t)((r > 255) ? 255 : ((r < 0) ? 0 : r));
    this->g = (u_int8_t)((g > 255) ? 255 : ((g < 0) ? 0 : g));
    this->b = (u_int8_t)((b > 255) ? 255 : ((b < 0) ? 0 : b));
    this->a = 255;
}

// Constructor with RGBA values as int
myColor::myColor(int r, int g, int b, int a) {
    this->r = (u_int8_t)((r > 255) ? 255 : ((r < 0) ? 0 : r));
    this->g = (u_int8_t)((g > 255) ? 255 : ((g < 0) ? 0 : g));
    this->b = (u_int8_t)((b > 255) ? 255 : ((b < 0) ? 0 : b));
    this->a = (u_int8_t)((a > 255) ? 255 : ((a < 0) ? 0 : a));
}

// Constructor with RGB values as float
myColor::myColor(float r, float g, float b) {
    this->r = (u_int8_t)((r > 1) ? 255 : ((r < 0) ? 0 : r * 255));
    this->g = (u_int8_t)((g > 1) ? 255 : ((g < 0) ? 0 : g * 255));
    this->b = (u_int8_t)((b > 1) ? 255 : ((b < 0) ? 0 : b * 255));
    this->a = 255;
}

// Constructor with RGBA values as float
myColor::myColor(float r, float g, float b, float a) {
    this->r = (u_int8_t)((r > 1) ? 255 : ((r < 0) ? 0 : r * 255));
    this->g = (u_int8_t)((g > 1) ? 255 : ((g < 0) ? 0 : g * 255));
    this->b = (u_int8_t)((b > 1) ? 255 : ((b < 0) ? 0 : b * 255));
    this->a = (u_int8_t)((a > 1) ? 255 : ((a < 0) ? 0 : a * 255));
}

// Constructor with RGB values as double
myColor::myColor(double r, double g, double b) {
    this->r = (u_int8_t)((r > 1) ? 255 : ((r < 0) ? 0 : r * 255));
    this->g = (u_int8_t)((g > 1) ? 255 : ((g < 0) ? 0 : g * 255));
    this->b = (u_int8_t)((b > 1) ? 255 : ((b < 0) ? 0 : b * 255));
    this->a = 255;
}

// Constructor with RGBA values as double
myColor::myColor(double r, double g, double b, double a) {
    this->r = (u_int8_t)((r > 1) ? 255 : ((r < 0) ? 0 : r * 255));
    this->g = (u_int8_t)((g > 1) ? 255 : ((g < 0) ? 0 : g * 255));
    this->b = (u_int8_t)((b > 1) ? 255 : ((b < 0) ? 0 : b * 255));
    this->a = (u_int8_t)((a > 1) ? 255 : ((a < 0) ? 0 : a * 255));
}

// Copy constructor
myColor::myColor(const myColor& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

// Copy constructor from sf::Color
myColor::myColor(const sf::Color& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}

// Destructor
myColor::~myColor() {
}