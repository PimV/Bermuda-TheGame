#include "Camera.h"


Camera::Camera(double x, double y, double width, double height, double mapWidth, double mapHeight)
	: x(x), y(y), width(width), height(height), mapWidth(mapWidth), mapHeight(mapHeight)
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

void Camera::setX(double x)
{
	if (x + this->getWidth() < this->mapWidth && x > 0) {
		this->x = x;
	}
}

void Camera::setY(double y)
{
	if (y + this->getHeight() < this->mapHeight && y > 0) {
		this->y = y;
	}
}

Camera::~Camera()
{
}
