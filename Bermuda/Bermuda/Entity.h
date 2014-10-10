#pragma once
class Entity
{
public:
	//Constructor
	Entity(int id);
	//Setters
	void setX(double x);
	void setY(double y);
	void setTempX(double x);
	void setTempY(double y);
	void setZ(double z);
	void setWidth(double width);
	void setHeight(double height);
	//Getters
	int getId();
	double getX();
	double getY();
	double getZ();
	double getWidth();
	double getHeight();
	//Destructor
	virtual ~Entity(void);
	double tempX;
	double tempY;

private:
	//Entity ID
	int id;
	//Entity Position
	double x;
	double y;
	double z;


	//Entity Size
	double width;
	double height;

};

