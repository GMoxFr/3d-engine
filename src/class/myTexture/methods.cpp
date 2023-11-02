#include "myTexture.hpp"

myColor myTexture::interpolate(double u, double v) const {
    auto x = static_cast<int>(u);
    auto y = static_cast<int>(v);

    x = x % width;
    y = y % height;
    if (x < 0) x += width;
    if (y < 0) y += height;

    return pixels.at(x + y * width);
}

myColor myTexture::getPixel(double u, double v) const {
    return interpolate(width * u, height * v);
}

void myTexture::bump(double u, double v, double& dhdu, double& dhdv) const {
    double x = u * width;
    double y = v * height;

    double vv = interpolate(x, y).getGrayScale();
    double vx = interpolate(x + 1, y).getGrayScale();
    double vy = interpolate(x, y + 1).getGrayScale();

    dhdu = vx - vv;
    dhdv = vy - vv;
}