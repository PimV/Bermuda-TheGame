#pragma once
#include "header_loader.h"
#include "ImageLoader.h"
#include <rapidjson/document.h>
#include <map>
#include <vector>

using namespace std;
using namespace rapidjson;

class MapLoader
{
private:
	void extractMapInfo(Document& d);
	void createTileSets(Value& tilesets);
	void createTiles(Value& tiles, int mapTileHeight, int mapTileWidth, int tileHeight, int tileWidth);
	void createObjects(Value& objects);
	void createSpawnPoints(Value& spawnpoints);
	void setPercentage(int percentage);
	map<int, string> objectClasses;
	vector<int> collisionVector;
	ImageLoader* imgLoader;
	int firstImgID;
	int mapHeight;
	int mapWidth;
	int startPosX;
	int startPosY;
	int loadPercentage;
	string loadStatus;
public:
	MapLoader();
	void loadMap();
	int getMapHeight();
	int getMapWidth();
	int getStartPosX();
	int getStartPosY();
	int getLoadPercentage();
	string getLoadStatus();
	virtual ~MapLoader();
};

