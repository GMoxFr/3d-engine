#include "myColor.hpp"

// Convert to sf::Color
sf::Color myColor::toSFMLColor() const
{
    return sf::Color(
        static_cast<u_int8_t>(r * 255.0),
        static_cast<u_int8_t>(g * 255.0),
        static_cast<u_int8_t>(b * 255.0),
        static_cast<u_int8_t>(a * 255.0));
}

// Convert from sf::Color
void myColor::fromSFMLColor(const sf::Color &c)
{
    r = static_cast<double>(c.r) / 255.0;
    g = static_cast<double>(c.g) / 255.0;
    b = static_cast<double>(c.b) / 255.0;
    a = static_cast<double>(c.a) / 255.0;
}

myColor myColor::darken(double factor)
{
    factor = my3d::clamp(factor);

    return myColor(
        r * factor,
        g * factor,
        b * factor,
        a);
}

double myColor::getGrayScale() const
{
    return (r + g + b) / 3.0;
}

myColor myColor::getRandColor()
{
    return myColor(
        rand() % 256,
        rand() % 256,
        rand() % 256);
}