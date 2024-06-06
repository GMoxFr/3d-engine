#include "myImage.hpp"

myColor myImage::getPixel(myPoint v)
{
	if (v.x < 0 || v.x >= width || v.y < 0 || v.y >= height)
	{
		return myColor::BLACK;
	}
	return pixels.at((height - v.y) * width + v.x);
}

void myImage::setPixel(myPoint v, myColor const &c, double z)
{
	if (v.x < 0 || v.x >= width || v.y < 0 || v.y >= height)
		return;

	unsigned int pos = (height - 1 - v.y) * width + v.x;

	if (zBuffer.at(pos) < z)
		return;

	zBuffer.at(pos) = z;
	pixels.at(pos) = c;
}

void myImage::setPixel(myVector3 v, myColor const &c)
{
	setPixel(myPoint(static_cast<int>(round(v.x)), static_cast<int>(round(v.z))), c, v.y);
}

myColorWithMetadata myImage::handleBounce(myVector3 start, myVector3 rayDirection, myShape const *baseShape, std::vector<std::unique_ptr<myShape>> const &shapes, std::vector<std::unique_ptr<myLight>> const &lights, double index, int depth)
{
	if (depth <= 0)
		return {myColor::BLACK, false, std::numeric_limits<double>::max()};

	myVector3 closestIntersection;
	myVector3 closestNormal;
	myColor closestColor;
	double minDistance = std::numeric_limits<double>::max();
	double d = 0;
	myShape *closestShape = nullptr;

	double u;
	double v;

	for (std::unique_ptr<myShape> const &shape : shapes)
	{
		if (shape.get() == baseShape)
			continue;

		d = shape->intersectDistance(start, rayDirection);
		if (d < minDistance && d > EPSILON)
		{
			closestShape = shape.get();
			minDistance = d;
		}
	}

	if (closestShape != nullptr)
	{
		(*closestShape).intersect(start, rayDirection, closestIntersection, closestNormal, closestColor, u, v);

		myColorWithMetadata newColor;
		newColor.color = (*closestShape).applyLighting(closestIntersection, closestNormal, closestColor, lights, shapes);
		newColor.modified = true;
		newColor.y = closestIntersection.y;
		if ((*closestShape).getReflection() > EPSILON)
		{
			myVector3 newDirection = rayDirection - closestNormal * 2 * (rayDirection * closestNormal);
			newColor.color += (handleBounce(closestIntersection, newDirection, closestShape, shapes, lights, (*closestShape).getFresnel(), depth - 1).color) * (*closestShape).getReflection();
		}
		if ((*closestShape).getRefraction() > EPSILON)
		{
			double n1 = index;
			double n2 = (*closestShape).getFresnel();
			double micro = n1 / n2;

			myVector3 refractedDir = micro * rayDirection + (-closestNormal) * (std::sqrt(1 - micro * micro * (1 - ((-closestNormal) * rayDirection) * ((-closestNormal) * rayDirection)))) - (micro * (-closestNormal) * ((-closestNormal) * rayDirection));
			newColor.color += (handleBounce(closestIntersection, refractedDir, closestShape, shapes, lights, (*closestShape).getFresnel(), depth - 1)).color * (*closestShape).getRefraction();
		}
		return newColor;
	}

	return {myColor::BLACK, false, std::numeric_limits<double>::max()};
}

void myImage::rayCast(myVector3 camera, std::vector<std::unique_ptr<myShape>> const &shapes, std::vector<std::unique_ptr<myLight>> const &lights)
{
	rayCast(camera, shapes, lights, 0, 0, width, height);
}

void myImage::rayCast(myVector3 camera, std::vector<std::unique_ptr<myShape>> const &shapes, std::vector<std::unique_ptr<myLight>> const &lights, int x1, int z1, int x2, int z2)
{
	for (int x = x1; x < x2; x++)
	{
		for (int z = z1; z < z2; z++)
		{
			myVector3 rayDirection = myVector3(x, 0, z) - camera;
			rayDirection.normalize();

			myColorWithMetadata newColor = handleBounce(camera, rayDirection, nullptr, shapes, lights, 1.0, 32);
			if (newColor.modified)
				setPixel(myPoint(x, z), newColor.color, 1);
		}
	}
}

void myImage::clear(myColor const &c)
{
	for (int i = 0; i < width * height; i++)
	{
		pixels[i] = c;
		zBuffer[i] = std::numeric_limits<double>::max();
	}
}

sf::Image myImage::toSFMLImage()
{
	sf::Image image;
	image.create(width, height);

	for (int i = 0; i < width * height; i++)
	{
		image.setPixel(i % width, i / width, pixels[i].toSFMLColor());
	}

	return image;
}

void myImage::toPNG(std::string const &filename)
{
	sf::Image image = toSFMLImage();
	image.saveToFile(filename);
}