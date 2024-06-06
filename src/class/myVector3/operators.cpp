#include "myVector3.hpp"

myVector3 &myVector3::operator+=(const myVector3 &v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

myVector3 &myVector3::operator-=(const myVector3 &v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

myVector3 &myVector3::operator*=(const double &d)
{
	x *= d;
	y *= d;
	z *= d;
	return *this;
}

myVector3 &myVector3::operator/=(const double &d)
{
	if (std::abs(d) < EPSILON)
	{
		throw DivisionByZeroException();
	}
	x /= d;
	y /= d;
	z /= d;
	return *this;
}

myVector3 myVector3::operator+(const myVector3 &v) const
{
	return myVector3(
		x + v.x,
		y + v.y,
		z + v.z);
}

myVector3 myVector3::operator-(const myVector3 &v) const
{
	return myVector3(
		x - v.x,
		y - v.y,
		z - v.z);
}

myVector3 myVector3::operator*(const double &d) const
{
	return myVector3(
		x * d,
		y * d,
		z * d);
}

myVector3 myVector3::operator/(const double &d) const
{
	if (std::abs(d) < EPSILON)
	{
		throw DivisionByZeroException();
	}
	return myVector3(
		x / d,
		y / d,
		z / d);
}

bool myVector3::operator==(const myVector3 &v) const
{
	return x == v.x && y == v.y && z == v.z;
}

bool myVector3::operator!=(const myVector3 &v) const
{
	return x != v.x || y != v.y || z != v.z;
}

bool myVector3::operator<(const myVector3 &v) const
{
	return this->squaredMagnitude() < v.squaredMagnitude();
}

bool myVector3::operator>(const myVector3 &v) const
{
	return this->squaredMagnitude() > v.squaredMagnitude();
}

bool myVector3::operator<=(const myVector3 &v) const
{
	return this->squaredMagnitude() <= v.squaredMagnitude();
}

bool myVector3::operator>=(const myVector3 &v) const
{
	return this->squaredMagnitude() >= v.squaredMagnitude();
}

myVector3 operator*(const double &d, const myVector3 &v)
{
	return myVector3(
		v.x * d,
		v.y * d,
		v.z * d);
}

myVector3 myVector3::operator-() const
{
	return myVector3(-x, -y, -z);
}

myVector3 myVector3::operator^(const myVector3 &v) const
{
	return myVector3(
		y * v.z - z * v.y,
		z * v.x - x * v.z,
		x * v.y - y * v.x);
}

double myVector3::operator*(const myVector3 &v) const
{
	return x * v.x + y * v.y + z * v.z;
}

std::ostream &operator<<(std::ostream &os, const myVector3 &v)
{
	os << "Vector3(" << v.x << ", " << v.y << ", " << v.z << ")";
	return os;
}