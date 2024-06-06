#include "mySphere.hpp"

void mySphere::draw(myImage &I, std::vector<std::unique_ptr<myLight>> const &L)
{
	const int uSteps = 1000;
	const int vSteps = 500;

	for (int i = 0; i < uSteps; i++)
	{
		double u = i * PRECISION;
		for (int j = 0; j < vSteps; j++)
		{
			double v = j * PRECISION - PI2;
			myVector3 pos(
				radius * my3d::cosf(v) * my3d::cosf(u) + center.x,
				radius * my3d::cosf(v) * my3d::sinf(u) + center.y,
				radius * my3d::sinf(v) + center.z);

			// Object
			myVector3 normal = pos - center;
			normal.normalize();
			myColor workingColor = getHasTexture() ? getTexture().getPixel(u / DPI, (v + PI / 2) / PI) : getColor();

			// Bump Map
			if (getHasBumpMap())
			{
				double dhdu = 0;
				double dhdv = 0;
				getBumpMap().bump(u / DPI, (v + PI / 2) / PI, dhdu, dhdv);

				myVector3 dMdu(
					-radius * my3d::cosf(v) * my3d::sinf(u),
					radius * my3d::cosf(v) * my3d::cosf(u),
					0);

				myVector3 dMdv(
					-radius * my3d::sinf(v) * my3d::cosf(u),
					-radius * my3d::sinf(v) * my3d::sinf(u),
					radius * my3d::cosf(v));

				double K = 0.01;
				myVector3 bumpNormal = normal + (K * ((dMdu ^ (dhdv * normal)) + (dMdv ^ (dhdu * normal))));
				bumpNormal.normalize();
				normal = bumpNormal;
			}

			// Draw
			I.setPixel(pos, applyLighting(pos, normal, workingColor, L, std::vector<std::unique_ptr<myShape>>()));
		}
	}
}

bool mySphere::intersect(myVector3 const &origin, myVector3 const &direction, myVector3 &intersection, myVector3 &normal, myColor &color, double &u, double &v)
{

	double a = direction * direction;
	double b = 2 * direction * (origin - center);
	double d = origin * origin - 2 * origin * center + center * center - radius * radius;

	double delta = b * b - 4 * a * d;

	if (delta < 0)
	{
		return false;
	}
	double t1 = (-b - my3d::sqrtf(delta)) / (2 * a);
	double t2 = (-b + my3d::sqrtf(delta)) / (2 * a);

	if (t1 < 0 && t2 < 0)
		return false;
	if (t1 > 0 && t2 > 0)
		intersection = origin + t1 * direction;
	if (t1 < 0 && t2 > 0)
		intersection = origin + t2 * direction;

	normal = intersection - center;
	normal.normalize();
	color = getColor();
	my3d::invertCoordSpherique(intersection, this->center, this->radius, u, v);
	color = getHasTexture() ? getTexture().getPixel(u / DPI, (v + PI / 2) / PI) : getColor();

	if (getHasBumpMap())
	{
		double dhdu = 0;
		double dhdv = 0;
		getBumpMap().bump(u / DPI, (v + PI / 2) / PI, dhdu, dhdv);

		myVector3 dMdu(
			-radius * my3d::cosf(v) * my3d::sinf(u),
			radius * my3d::cosf(v) * my3d::cosf(u),
			0);

		myVector3 dMdv(
			-radius * my3d::sinf(v) * my3d::cosf(u),
			-radius * my3d::sinf(v) * my3d::sinf(u),
			radius * my3d::cosf(v));

		double K = 0.1;
		myVector3 bumpNormal = normal + (K * ((dMdu ^ (dhdv * normal)) + (dMdv ^ (dhdu * normal))));
		bumpNormal.normalize();
		normal = bumpNormal;
	}

	return true;
}

bool mySphere::intersect(myVector3 const &origin, myVector3 const &direction, myVector3 &intersection, myVector3 &normal, myColor &color)
{

	double a = direction * direction;
	double b = 2 * direction * (origin - center);
	double d = origin * origin - 2 * origin * center + center * center - radius * radius;

	double delta = b * b - 4 * a * d;

	if (delta < 0)
	{
		return false;
	}
	double t1 = (-b - my3d::sqrtf(delta)) / (2 * a);
	double t2 = (-b + my3d::sqrtf(delta)) / (2 * a);

	if (t1 < 0 && t2 < 0)
		return false;
	if (t1 > 0 && t2 > 0)
		intersection = origin + t1 * direction;
	if (t1 < 0 && t2 > 0)
		intersection = origin + t2 * direction;

	normal = intersection - center;
	normal.normalize();
	color = getColor();
	double u, v;
	my3d::invertCoordSpherique(intersection, this->center, this->radius, u, v);
	color = getHasTexture() ? getTexture().getPixel(u / DPI, (v + PI / 2) / PI) : getColor();

	if (getHasBumpMap())
	{
		double dhdu = 0;
		double dhdv = 0;
		getBumpMap().bump(u / DPI, (v + PI / 2) / PI, dhdu, dhdv);

		myVector3 dMdu(
			-radius * my3d::cosf(v) * my3d::sinf(u),
			radius * my3d::cosf(v) * my3d::cosf(u),
			0);

		myVector3 dMdv(
			-radius * my3d::sinf(v) * my3d::cosf(u),
			-radius * my3d::sinf(v) * my3d::sinf(u),
			radius * my3d::cosf(v));

		double K = 0.1;
		myVector3 bumpNormal = normal + (K * ((dMdu ^ (dhdv * normal)) + (dMdv ^ (dhdu * normal))));
		bumpNormal.normalize();
		normal = bumpNormal;
	}

	return true;
}

bool mySphere::intersect(myVector3 const &origin, myVector3 const &direction)
{
	double a = direction * direction;
	double b = 2 * direction * (origin - center);
	double d = origin * origin - 2 * origin * center + center * center - radius * radius;

	double delta = b * b - 4 * a * d;

	if (delta < 0)
	{
		return false;
	}
	double t1 = (-b - my3d::sqrtf(delta)) / (2 * a);
	double t2 = (-b + my3d::sqrtf(delta)) / (2 * a);

	if (t1 < 0 && t2 < 0)
		return false;
	return true;
}

double mySphere::intersectDistance(myVector3 const &origin, myVector3 const &direction)
{
	double a = direction * direction;
	double b = 2 * direction * (origin - center);
	double d = origin * origin - 2 * origin * center + center * center - radius * radius;

	double delta = b * b - 4 * a * d;

	if (delta < 0)
	{
		return -1;
	}
	double t1 = (-b - my3d::sqrtf(delta)) / (2 * a);
	double t2 = (-b + my3d::sqrtf(delta)) / (2 * a);

	if (t1 < 0 && t2 < 0)
		return -1;
	if (t1 > 0 && t2 > 0)
		return t1;
	if (t1 < 0 && t2 > 0)
		return t2;
	return -1;
}