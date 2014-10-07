#include "Camera.h"


Camera::Camera(int x, int y, int width, int height)
	: x(x), y(y), width(width), height(height)
{
}

int Camera::getX()
{
	return x;
}

int Camera::getY()
{
	return y;
}

int Camera::getWidth()
{
	return width;
}

int Camera::getHeight()
{
	return height;
}

Camera::~Camera()
{
}
