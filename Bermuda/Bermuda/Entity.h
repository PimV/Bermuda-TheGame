#pragma once
class Entity
{
public:
	//Constructor
	Entity(int id, double x, double y, int chunkSize);
	//Setters
	void setX(double x);
	void setY(double y);
	void setTempX(double x);
	void setTempY(double y);
	void setZ(double z);
	void setWidth(double width);
	void setHeight(double height);
	void setChunkSize(int chunkSize);
	void setChunks(); //According to the chunksize
	//Getters
	int getId();
	int getChunkSize();
	int getChunkY();
	int getChunkX();
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

	//Entity chunk
	int chunkSize;
	int chunkY;
	int chunkX;
};

