#include "Camera.h"


Camera::Camera(double x, double y, double width, double height)
	: x(x), y(y), width(width), height(height)
{
}

double Camera::getX()
{
	return x;
}

double Camera::getY()
{
	return y;
}

double Camera::getWidth()
{
	return width;
}

double Camera::getHeight()
{
	return height;
}

Camera::~Camera()
{
}
