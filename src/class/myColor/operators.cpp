#include "myColor.hpp"

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

// Conversion operator to sf::Color
myColor::operator sf::Color() const {
    return sf::Color(r, g, b, a);
}