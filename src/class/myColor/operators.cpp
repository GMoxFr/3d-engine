#include "myColor.hpp"

// Assignment operator for sf::Color
myColor &myColor::operator=(const sf::Color &c)
{
    r = static_cast<double>(c.r) / 255.0;
    g = static_cast<double>(c.g) / 255.0;
    b = static_cast<double>(c.b) / 255.0;
    a = static_cast<double>(c.a) / 255.0;

    return *this;
}

// Addition operator
myColor myColor::operator+(const myColor &c) const
{
    myColor result;
    result.r = my3d::clamp(r + c.r);
    result.g = my3d::clamp(g + c.g);
    result.b = my3d::clamp(b + c.b);
    result.a = my3d::clamp(a + c.a);

    return result;
}

// Subtraction operator
myColor myColor::operator-(const myColor &c) const
{
    myColor result;
    result.r = my3d::clamp(r - c.r);
    result.g = my3d::clamp(g - c.g);
    result.b = my3d::clamp(b - c.b);
    result.a = my3d::clamp(a - c.a);

    return result;
}

// Multiplication operator
myColor myColor::operator*(const myColor &c) const
{
    myColor result;
    result.r = my3d::clamp(r * c.r);
    result.g = my3d::clamp(g * c.g);
    result.b = my3d::clamp(b * c.b);
    result.a = my3d::clamp(a * c.a);

    return result;
}

// Addition assignment operator
myColor &myColor::operator+=(const myColor &c)
{
    r = my3d::clamp(r + c.r);
    g = my3d::clamp(g + c.g);
    b = my3d::clamp(b + c.b);
    a = my3d::clamp(a + c.a);

    return *this;
}

// Subtraction assignment operator
myColor &myColor::operator-=(const myColor &c)
{
    r = my3d::clamp(r - c.r);
    g = my3d::clamp(g - c.g);
    b = my3d::clamp(b - c.b);
    a = my3d::clamp(a - c.a);

    return *this;
}

// Multiplication assignment operator
myColor &myColor::operator*=(const myColor &c)
{
    r = my3d::clamp(r * c.r);
    g = my3d::clamp(g * c.g);
    b = my3d::clamp(b * c.b);
    a = my3d::clamp(a * c.a);

    return *this;
}

// Multiplication operator with a double
myColor myColor::operator*(double factor) const
{
    myColor result;
    result.r = my3d::clamp(r * factor);
    result.g = my3d::clamp(g * factor);
    result.b = my3d::clamp(b * factor);
    result.a = my3d::clamp(a * factor);

    return result;
}

// Division operator with a double
myColor myColor::operator/(double factor) const
{
    if (std::abs(factor) < EPSILON)
    {
        throw DivisionByZeroException();
    }
    myColor result;
    result.r = my3d::clamp(r / factor);
    result.g = my3d::clamp(g / factor);
    result.b = my3d::clamp(b / factor);
    result.a = my3d::clamp(a / factor);

    return result;
}

// Multiplication assignment operator with a double
myColor &myColor::operator*=(double factor)
{
    r = my3d::clamp(r * factor);
    g = my3d::clamp(g * factor);
    b = my3d::clamp(b * factor);
    a = my3d::clamp(a * factor);

    return *this;
}

// Division assignment operator with a double
myColor &myColor::operator/=(double factor)
{
    if (std::abs(factor) < EPSILON)
    {
        throw DivisionByZeroException();
    }
    r = my3d::clamp(r / factor);
    g = my3d::clamp(g / factor);
    b = my3d::clamp(b / factor);
    a = my3d::clamp(a / factor);

    return *this;
}

// Equality operator
bool operator==(const myColor &lhs, const myColor &rhs)
{
    return (lhs.r == rhs.r && lhs.g == rhs.g && lhs.b == rhs.b && lhs.a == rhs.a);
}

// Inequality operator
bool operator!=(const myColor &lhs, const myColor &rhs)
{
    return !(lhs == rhs);
}

// Negation operator
myColor myColor::operator-() const
{
    myColor result;
    result.r = 1.0 - r;
    result.g = 1.0 - g;
    result.b = 1.0 - b;
    result.a = 1.0 - a;

    return result;
}

// Output stream operator
std::ostream &operator<<(std::ostream &os, const myColor &c)
{
    os << "Color(" << (int)c.r << ", " << (int)c.g << ", " << (int)c.b << ", " << (int)c.a << ")";
    return os;
}

// Conversion operator to sf::Color
myColor::operator sf::Color() const
{
    return sf::Color(
        static_cast<u_int8_t>(r * 255.0),
        static_cast<u_int8_t>(g * 255.0),
        static_cast<u_int8_t>(b * 255.0),
        static_cast<u_int8_t>(a * 255.0));
}