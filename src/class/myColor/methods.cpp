#include "myColor.hpp"

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

myColor myColor::darken(double factor) {
    if (factor < 0.0) factor = 0.0;
    if (factor > 1.0) factor = 1.0;

    return myColor(
        static_cast<u_int8_t>(r * factor),
        static_cast<u_int8_t>(g * factor),
        static_cast<u_int8_t>(b * factor),
        a
    );
}