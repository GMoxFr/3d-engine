#include "3dengine.hpp"

// Convert to sf::Color
sf::Color myColor::toSFMLColor() {
    return sf::Color(r, g, b, a);
}

// Convert from sf::Color
void myColor::fromSFMLColor(const sf::Color& c) {
    r = c.r;
    g = c.g;
    b = c.b;
    a = c.a;
}