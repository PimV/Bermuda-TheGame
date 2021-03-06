#pragma once

class Entity
{
public:
	//Constructor
	Entity(int id, double x, double y);
	//Setters
	void setX(double x);
	void setY(double y);
	void setZ(double z);
	void setWidth(double width);
	void setHeight(double height);
	void setChunks(); //According to the chunksize
	void setEnabled(bool enabled);
	//Getters
	int getId();
	int getChunkY();
	int getChunkX();
	double getX();
	double getY();
	double getZ();
	double getWidth();
	double getHeight();
	double getCenterX();
	double getCenterY();
	bool getEnabled();
	bool getHighlighted();
	void setHighlighted(bool highlighted);

	//Destructor
	virtual ~Entity();

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

	//Entity chunk
	int chunkY;
	int chunkX;

	bool highlighted;

	bool enabled;
};

