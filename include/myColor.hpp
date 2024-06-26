#pragma once

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>

#include "my3d.hpp"
#include "exceptions.hpp"

class myColor
{
public:
	// ATTRIBUTES
	double r;
	double g;
	double b;
	double a;

	// CONSTRUCTORS
	myColor();
	myColor(u_int8_t r, u_int8_t g, u_int8_t b, u_int8_t a = 255);
	myColor(int r, int g, int b, int a = 255);
	explicit myColor(const sf::Color &c);
	myColor(double r, double g, double b, double a = 1.0);
	explicit myColor(const std::vector<int> &components);

	// OPERATORS
	myColor &operator=(const sf::Color &c);

	myColor operator+(const myColor &c) const;
	myColor operator-(const myColor &c) const;
	myColor operator*(const myColor &c) const;

	myColor &operator+=(const myColor &c);
	myColor &operator-=(const myColor &c);
	myColor &operator*=(const myColor &c);

	myColor operator*(double factor) const;
	myColor operator/(double factor) const;
	myColor &operator*=(double factor);
	myColor &operator/=(double factor);

	friend bool operator==(const myColor &lhs, const myColor &rhs);
	friend bool operator!=(const myColor &lhs, const myColor &rhs);

	myColor operator-() const;

	friend std::ostream &operator<<(std::ostream &os, const myColor &c);

	explicit operator sf::Color() const;

	// METHODS
	sf::Color toSFMLColor() const;
	void fromSFMLColor(const sf::Color &c);
	myColor darken(double factor);
	double getGrayScale() const;

	// STATIC METHODS
	static myColor getRandColor();

	// DEFAULT COLORS
	static const myColor BLACK;
	static const myColor WHITE;
	static const myColor RED;
	static const myColor GREEN;
	static const myColor BLUE;
	static const myColor YELLOW;
	static const myColor MAGENTA;
	static const myColor CYAN;

	static const myColor PINK;
	static const myColor ORANGE;
	static const myColor PURPLE;
	static const myColor BROWN;
	static const myColor GOLD;
	static const myColor SILVER;
	static const myColor GRAY;

	static const myColor TRANSPARENT;

	static const myColor AMBIENT_LIGHT;
};