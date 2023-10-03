#include "3dengine.hpp"

// Assignment operator for myColor
myColor& myColor::operator=(const myColor& c) {
    if (this != &c) {
        r = c.r;
        g = c.g;
        b = c.b;
        a = c.a;
    }

    return *this;
}

// Assignment operator for sf::Color
myColor& myColor::operator=(const sf::Color& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;

    return *this;
}

// Addition assignment operator
myColor& myColor::operator+=(const myColor& c) {
    r = ((int)r + (int)c.r > 255) ? 255 : r + c.r;
    g = ((int)g + (int)c.g > 255) ? 255 : g + c.g;
    b = ((int)b + (int)c.b > 255) ? 255 : b + c.b;
    a = ((int)a + (int)c.a > 255) ? 255 : a + c.a;

    return *this;
}

// Addition operator
myColor operator+(const myColor& lhs, const myColor& rhs) {
    myColor c;
    c.r = lhs.r + rhs.r;
    c.g = lhs.g + rhs.g;
    c.b = lhs.b + rhs.b;
    c.a = lhs.a + rhs.a;

    return c;
}

// Subtraction assignment operator
myColor& myColor::operator-=(const myColor& c) {
    r = ((int)r - (int)c.r < 0) ? 0 : r - c.r;
    g = ((int)g - (int)c.g < 0) ? 0 : g - c.g;
    b = ((int)b - (int)c.b < 0) ? 0 : b - c.b;
    a = ((int)a - (int)c.a < 0) ? 0 : a - c.a;

    return *this;
}

// Subtraction operator
myColor operator-(const myColor& lhs, const myColor& rhs) {
    myColor c;
    c.r = lhs.r - rhs.r;
    c.g = lhs.g - rhs.g;
    c.b = lhs.b - rhs.b;
    c.a = lhs.a - rhs.a;

    return c;
}

// Multiplication assignment operator with float
myColor& myColor::operator*=(float factor) {
    r = ((int)r * factor > 255) ? 255 : r * factor;
    g = ((int)g * factor > 255) ? 255 : g * factor;
    b = ((int)b * factor > 255) ? 255 : b * factor;
    a = ((int)a * factor > 255) ? 255 : a * factor;

    return *this;
}

// Multiplication operator with float
myColor operator*(const myColor& c, float factor) {
    myColor result;
    result.r = ((int)c.r * factor > 255) ? 255 : c.r * factor;
    result.g = ((int)c.g * factor > 255) ? 255 : c.g * factor;
    result.b = ((int)c.b * factor > 255) ? 255 : c.b * factor;
    result.a = ((int)c.a * factor > 255) ? 255 : c.a * factor;

    return result;
}

// Multiplication operator with float
myColor operator*(float factor, const myColor& c) {
    myColor result;
    result.r = ((int)c.r * factor > 255) ? 255 : c.r * factor;
    result.g = ((int)c.g * factor > 255) ? 255 : c.g * factor;
    result.b = ((int)c.b * factor > 255) ? 255 : c.b * factor;
    result.a = ((int)c.a * factor > 255) ? 255 : c.a * factor;

    return result;
}

// Multiplication assignment operator with myColor
myColor& myColor::operator*=(const myColor& c) {
    r = ((int)r * (int)c.r > 255) ? 255 : r * c.r;
    g = ((int)g * (int)c.g > 255) ? 255 : g * c.g;
    b = ((int)b * (int)c.b > 255) ? 255 : b * c.b;
    a = ((int)a * (int)c.a > 255) ? 255 : a * c.a;

    return *this;
}

// Multiplication operator with myColor
myColor operator*(const myColor& lhs, const myColor& rhs) {
    myColor result;
    result.r = ((int)lhs.r * (int)rhs.r > 255) ? 255 : lhs.r * rhs.r;
    result.g = ((int)lhs.g * (int)rhs.g > 255) ? 255 : lhs.g * rhs.g;
    result.b = ((int)lhs.b * (int)rhs.b > 255) ? 255 : lhs.b * rhs.b;
    result.a = ((int)lhs.a * (int)rhs.a > 255) ? 255 : lhs.a * rhs.a;

    return result;
}

// Division assignment operator with float
myColor& myColor::operator/=(float factor) {
    r = ((int)r / factor < 0) ? 0 : r / factor;
    g = ((int)g / factor < 0) ? 0 : g / factor;
    b = ((int)b / factor < 0) ? 0 : b / factor;
    a = ((int)a / factor < 0) ? 0 : a / factor;

    return *this;
}

// Division operator with float
myColor operator/(const myColor& c, float factor) {
    myColor result;
    result.r = ((int)c.r / factor < 0) ? 0 : c.r / factor;
    result.g = ((int)c.g / factor < 0) ? 0 : c.g / factor;
    result.b = ((int)c.b / factor < 0) ? 0 : c.b / factor;
    result.a = ((int)c.a / factor < 0) ? 0 : c.a / factor;

    return result;
}

// Division assignment operator with myColor
myColor& myColor::operator/=(const myColor& c) {
    r = ((int)r / (int)c.r < 0) ? 0 : r / c.r;
    g = ((int)g / (int)c.g < 0) ? 0 : g / c.g;
    b = ((int)b / (int)c.b < 0) ? 0 : b / c.b;
    a = ((int)a / (int)c.a < 0) ? 0 : a / c.a;

    return *this;
}

// Division operator with myColor
myColor operator/(const myColor& lhs, const myColor& rhs) {
    myColor result;
    result.r = ((int)lhs.r / (int)rhs.r < 0) ? 0 : lhs.r / rhs.r;
    result.g = ((int)lhs.g / (int)rhs.g < 0) ? 0 : lhs.g / rhs.g;
    result.b = ((int)lhs.b / (int)rhs.b < 0) ? 0 : lhs.b / rhs.b;
    result.a = ((int)lhs.a / (int)rhs.a < 0) ? 0 : lhs.a / rhs.a;

    return result;
}

// Equality operator
bool operator==(const myColor& lhs, const myColor& rhs) {
    return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a);
}

// Inequality operator
bool operator!=(const myColor& lhs, const myColor& rhs) {
    return !(lhs == rhs);
}

// Negation operator
myColor myColor::operator-() const {
    myColor result;
    result.r = 255 - r;
    result.g = 255 - g;
    result.b = 255 - b;
    result.a = 255 - a;

    return result;
}

// Output stream operator
std::ostream& operator<<(std::ostream& os, const myColor& c) {
    os << "Color(" << (int)c.r << ", " << (int)c.g << ", " << (int)c.b << ", " << (int)c.a << ")";
    return os;
}