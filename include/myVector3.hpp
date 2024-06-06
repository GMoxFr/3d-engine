#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "constants.hpp"
#include "exceptions.hpp"

class myVector3
{
public:
	// ATTRIBUTES
	double x;
	double y;
	double z;

	// CONSTRUCTORS
	myVector3(double x = 0.0, double y = 0.0, double z = 0.0);
	explicit myVector3(const std::vector<double> &v);
	~myVector3() = default;

	// OPERATORS
	myVector3 &operator+=(const myVector3 &v);
	myVector3 &operator-=(const myVector3 &v);
	myVector3 &operator*=(const double &d);
	myVector3 &operator/=(const double &d);

	myVector3 operator+(const myVector3 &v) const;
	myVector3 operator-(const myVector3 &v) const;
	myVector3 operator*(const double &d) const;
	myVector3 operator/(const double &d) const;

	bool operator==(const myVector3 &v) const;
	bool operator!=(const myVector3 &v) const;
	bool operator<(const myVector3 &v) const;
	bool operator>(const myVector3 &v) const;
	bool operator<=(const myVector3 &v) const;
	bool operator>=(const myVector3 &v) const;

	friend myVector3 operator*(const double &d, const myVector3 &v);

	myVector3 operator-() const;

	myVector3 operator^(const myVector3 &v) const;
	double operator*(const myVector3 &v) const;

	friend std::ostream &operator<<(std::ostream &os, const myVector3 &v);

	// METHODS
	double dot(const myVector3 &v) const;
	myVector3 cross(const myVector3 &v) const;

	double magnitude() const;
	double squaredMagnitude() const;

	bool isZero() const;

	void normalize();
	myVector3 normalized() const;

	double distanceTo(const myVector3 &v) const;
	double squaredDistanceTo(const myVector3 &v) const;

	double angleBetween(const myVector3 &v) const;

	myVector3 findPerpendicular() const;
	myVector3 rotateVector(const myVector3 &axis, double angle) const;
	myVector3 rotateVector(const myVector3 &rotation) const;

	static const myVector3 CAMERA;

	static const myVector3 ZERO;

	static const myVector3 UP;
	static const myVector3 DOWN;
	static const myVector3 LEFT;
	static const myVector3 RIGHT;
	static const myVector3 FORWARD;
	static const myVector3 BACKWARD;

	static const myVector3 BOTTOM_LEFT;
	static const myVector3 BOTTOM_RIGHT;
	static const myVector3 TOP_LEFT;
	static const myVector3 TOP_RIGHT;
};