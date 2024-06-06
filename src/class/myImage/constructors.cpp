#include "myImage.hpp"

myImage::myImage(int width, int height, myColor const &c) : width(width),
															height(height),
															pixels(width * height, c),
															zBuffer(width * height, std::numeric_limits<double>::max())
{
}