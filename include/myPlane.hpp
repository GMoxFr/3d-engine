#pragma once

#include "myVector3.hpp"

class myPlane
{
private:
	myVector3 point;  // A point on the plane
	myVector3 normal; // The normal vector of the plane

public:
	myPlane(const myVector3 &point, const myVector3 &normal)
		: point(point), normal(normal.normalized()) {}

	// Check if a point is in the direction of the plane's normal
	bool isPointInNormalDirection(const myVector3 &p) const
	{
		return (p - point).dot(normal) > 0;
	}

	// Check if a point is in the opposite direction of the plane's normal
	bool isPointInOppositeDirection(const myVector3 &p) const
	{
		return (p - point).dot(normal) < 0;
	}

	// Getters
	const myVector3 &getPoint() const { return point; }
	const myVector3 &getNormal() const { return normal; }
};
