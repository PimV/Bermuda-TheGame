#pragma once
class Camera
{
private:
	double x;
	double y;
	double width;
	double height;
public:
	Camera(double x, double y, double width, double height);
	double getX();
	double getY();
	double getWidth();
	double getHeight();
	~Camera();
};

