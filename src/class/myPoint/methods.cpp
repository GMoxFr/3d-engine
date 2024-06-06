#include "myPoint.hpp"

double myPoint::distance(const myPoint &p) const
{
	return sqrt(pow(p.x - x, 2) + pow(p.y - y, 2));
}