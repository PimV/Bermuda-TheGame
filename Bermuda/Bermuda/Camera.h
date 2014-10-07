#pragma once
class Camera
{
private:
	int x;
	int y;
	int width;
	int height;
public:
	Camera(int x, int y, int width, int height);
	int getX();
	int getY();
	int getWidth();
	int getHeight();
	~Camera();
};

