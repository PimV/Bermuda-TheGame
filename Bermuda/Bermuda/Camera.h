#pragma once
class Camera
{
private:
	double x;
	double y;
	double width;
	double height;
	double mapWidth;
	double mapHeight;
public:
	//TODO: camera movement methodes. (Moet in dezelfde richting en met dezelfde snelheid als de speler bewegen)
	Camera(double x, double y, double width, double height, double mapWidth, double mapHeight);
	double getX();
	double getY();
	double getWidth();
	double getHeight();

	void setX(double x);
	void setY(double y);

	virtual ~Camera();
};

