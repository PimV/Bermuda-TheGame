#pragma once
#include "header_loader.h"
#include <rapidjson/document.h>

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
public:
	MapLoader();
	void loadMap();
	~MapLoader();
};

