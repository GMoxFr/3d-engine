#include "myTexture.hpp"

myColor myTexture::interpolate(double u, double v) {
    int x = static_cast<int>(u);
    int y = static_cast<int>(v);

    x = x % width;
    y = y % height;
    if (x < 0) x += width;
    if (y < 0) y += height;

    return pixels[x + y * width];
}

myColor myTexture::getPixel(double u, double v) {
    return interpolate(width * u, height * v);
}

void myTexture::bump(double u, double v, double& dhdu, double& dhdv) {
    double x = u * width;
    double y = v * height;

    double vv = interpolate(x, y).getGrayScale();
    double vx = interpolate(x + 1, y).getGrayScale();
    double vy = interpolate(x, y + 1).getGrayScale();

    dhdu = vx - vv;
    dhdv = vy - vv;
}