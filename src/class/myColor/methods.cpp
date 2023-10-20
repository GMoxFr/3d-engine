#include "myColor.hpp"

// Convert to sf::Color
sf::Color myColor::toSFMLColor() {
    return sf::Color(
        static_cast<u_int8_t>(r * 255.0),
        static_cast<u_int8_t>(g * 255.0),
        static_cast<u_int8_t>(b * 255.0),
        static_cast<u_int8_t>(a * 255.0)
    );
}

// Convert from sf::Color
void myColor::fromSFMLColor(const sf::Color& c) {
    r = static_cast<double>(c.r) / 255.0;
    g = static_cast<double>(c.g) / 255.0;
    b = static_cast<double>(c.b) / 255.0;
    a = static_cast<double>(c.a) / 255.0;
}

myColor myColor::darken(double factor) {
    if (factor < 0.0) factor = 0.0;
    if (factor > 1.0) factor = 1.0;

    return myColor(
        r * factor,
        g * factor,
        b * factor,
        a
    );
}