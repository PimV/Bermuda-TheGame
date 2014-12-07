#include "MapLoader.h"
#include "Tile.h"
#include "Tree.h"
#include "AppleTree.h"
#include "Rock.h"
#include "RockSpikes.h"
#include "GoldRock.h"
#include "Ice.h"
#include "Carrot.h"
#include "Fish.h"
#include "Pillar.h"
#include "RuinStatue.h"
#include "EasterHead.h"
#include "Cactus.h"
#include "SnowTree.h"
#include "InteractableCactus.h"
#include "CollidableTile.h"
#include "SpawnPoint.h"
#include "LoadingState.h"

#include <rapidjson/stringbuffer.h>
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <Windows.h>
#include <math.h>

MapLoader::MapLoader()
{
	this->imgLoader = PlayState::Instance()->getImageLoader();
}

void MapLoader::setPercentage(int percentage)
{
	this->loadPercentage = percentage;
	LoadingState::Instance()->setPercentage(percentage);
	LoadingState::Instance()->draw();
}

void MapLoader::loadMap()
{
	LoadingState::Instance()->init(nullptr);
	this->setPercentage(0);
	this->firstImgID = imgLoader->getCurrentImageCount();
	double startLoadPercentage = 0;
	double loadWeight = 10;
	double totalJSONLines = -1;
	double processedJSONLines = 0;
	int tempPercentage = loadPercentage;
	loadStatus = "Reading map file.";

	//Create file stream.
	string executableRoot = SDL_GetBasePath();
	string fileName = executableRoot + "Map.json";
	ifstream stream(fileName);
	if(!stream.is_open())
	{
		cout << "Could not load map. File " + fileName + " could not be found!" << endl;
		return;
	}

	//Read entire file into a string.
	string json;
	string line;
	bool firstLine = true;
	while (getline(stream, line))
	{
		if (firstLine)
		{
			firstLine = false;
			//First line contains total file lines.
			istringstream iss(line);
			string type;
			iss >> type >> totalJSONLines;
			if (type == "JsonLines:" && totalJSONLines > 0)
			{
				continue;
			}
			else
			{
				cout << "Missing line count. Can't calculate file load percentage." << endl;
				totalJSONLines = 0;
			}
		}

		json += line;

		if (totalJSONLines > 0)
		{
			processedJSONLines++;
			tempPercentage = startLoadPercentage + ((processedJSONLines / totalJSONLines) * loadWeight);
			if (tempPercentage != this->loadPercentage) {
				this->setPercentage(tempPercentage);
			}
		}
	}
	this->setPercentage(loadWeight); //Just to be sure (file might contain wrong line count),  set the loadPercentage to the total loadWeight of this part. 

	//Close stream.
	stream.close();

	//Parse JSON string into DOM.
	Document d;
	d.Parse(json.c_str());

	extractMapInfo(d);
	LoadingState::Instance()->cleanup();
}

void MapLoader::extractMapInfo(Document& d)
{
	loadStatus = "Creating chunks.";

	//Get general map information
	int mapTileHeight = d["height"].GetInt();
	int mapTileWidth = d["width"].GetInt();
	int tileHeight = d["tileheight"].GetInt();
	int tileWidth = d["tilewidth"].GetInt();

	mapHeight = mapTileHeight * tileHeight;
	mapWidth = mapTileWidth * tileWidth;

	//Initialize the containers
	PlayState::Instance()->getMainEntityContainer()->initContainerSizes(mapHeight, mapWidth);
	Value& tilesets = d["tilesets"];
	createTileSets(tilesets);

	for(int i = 0; i < d["layers"].Capacity(); i++)
	{
		Value& layer = d["layers"][i];
		string layerName = layer["name"].GetString();

		if(layerName == "Tiles")
		{
			createTiles(layer["data"], mapTileHeight, mapTileWidth, tileHeight, tileWidth);
		}
		else if (layerName == "Objects")
		{
			createObjects(layer["objects"]);
		}
		else if (layerName == "SpawnPoints")
		{
			createSpawnPoints(layer["objects"]);
		}
		loadStatus = "Map loading finished.";
	}
}

void MapLoader::createTileSets(Value& tilesets)
{
	double startLoadPercentage = loadPercentage;
	double loadWeight = 20;
	double totalTilesets = tilesets.Capacity();
	double processedTilesets = 0;
	int tempPercentage = loadPercentage;
	loadStatus = "Loading tilesets.";

	for(int i = 0; i < tilesets.Capacity(); i++)
	{
		Value& tileset = tilesets[i];
		string imgName = tileset["image"].GetString();
		int tileHeight = tileset["tileheight"].GetInt();
		int tileWidth = tileset["tilewidth"].GetInt();
		int firstId = tileset["firstgid"].GetInt();

		imgLoader->loadTileset(imgName, tileWidth, tileHeight);

		if(tileset.HasMember("tileproperties"))
		{
			for(Value::ConstMemberIterator it=tileset["tileproperties"].MemberBegin(); it != tileset["tileproperties"].MemberEnd(); it++) {
				for(Value::ConstMemberIterator it2=tileset["tileproperties"][it->name].MemberBegin(); it2 != tileset["tileproperties"][it->name].MemberEnd(); it2++) {
					string name = it2->name.GetString();
					int objectID = firstId+stoi(it->name.GetString());
					if (name == "Type")
					{
						objectClasses[objectID] = it2->value.GetString();
					}
					else if (name == "Collision")
					{
						collisionVector.push_back(objectID);
					}
				}
			}
		}
		processedTilesets++;
		tempPercentage = startLoadPercentage + ((processedTilesets / totalTilesets) * loadWeight);
		if (tempPercentage != this->loadPercentage) {
			this->setPercentage(tempPercentage);
		}

	}
}

void MapLoader::createTiles(Value& tiles, int mapTileHeight, int mapTileWidth, int tileHeight, int tileWidth)
{
	double startLoadPercentage = loadPercentage;
	double loadWeight = 40;
	double totalTiles = mapTileHeight * mapTileWidth;
	double processedTiles = 0;
	int tempPercentage = loadPercentage;
	loadStatus = "Creating tiles.";

	for (int y = 0; y < mapTileHeight; y++)
	{
		for (int x = 0; x < mapTileWidth; x++)
		{
			int tileID = tiles[(y*mapTileWidth)+x].GetInt();

			if(find(collisionVector.begin(), collisionVector.end(), tileID) != collisionVector.end())
			{
				//Tile is in collision vector. Create collisionTile.
				CollidableTile* tile = new CollidableTile(tileID, x*tileWidth, y*tileHeight, imgLoader->getMapImage(firstImgID + tileID));
			}
			else
			{
				//Tile is not in collision vector. Creating normal tile.
				Tile* tile = new Tile(tileID, x*tileWidth, y*tileHeight, imgLoader->getMapImage(firstImgID + tileID));				
			}
			processedTiles++;
			tempPercentage = startLoadPercentage + ((processedTiles / totalTiles) * loadWeight);
			if (tempPercentage != this->loadPercentage) {
				this->setPercentage(tempPercentage);
			}
		}
	}
}

void MapLoader::createObjects(Value& objects)
{
	//Possibly use something like this to create objects from strings
	/*map_type map;
	map["DerivedA"] = &createInstance<DerivedA>;
	map["DerivedB"] = &createInstance<DerivedB>;
	//And then you can do
	return map[some_string]();*/
	//Parameters could be a problem with this though. 
	//TODO: Create object factory?

	double startLoadPercentage = loadPercentage;
	double loadWeight = 20;
	double totalObjects = objects.Capacity();
	double processedObjects = 0;
	int tempPercentage = loadPercentage;
	loadStatus = "Creating objects.";

	for(int j = 0; j < objects.Capacity(); j++)
	{
		Value& object = objects[j];
		int objectID = object["gid"].GetInt();
		Image* objectImg = imgLoader->getMapImage(firstImgID + objectID);
		double objectX = object["x"].GetDouble();
		double objectY = object["y"].GetDouble() - objectImg->getHeight(); // -getHeight() Because all 'tiled' objects use bottom left for image positioning;

		//TODO: Any better way to do this?
		if(objectClasses[objectID] == "Tree")
		{
			new Tree(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
		}
		else if(objectClasses[objectID] == "TreeStump")
		{
			Tree* tree = new Tree(objectID, objectX, objectY, imgLoader->getMapImage(firstImgID + objectID - 1), objectImg);
			tree->setDestroyedState();
		}
		else if(objectClasses[objectID] == "AppleTree")
		{
			new AppleTree(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1), imgLoader->getMapImage(firstImgID + objectID + 2));
		}
		else if(objectClasses[objectID] == "AppleTreeEmpty")
		{
			AppleTree* tree = new AppleTree(objectID, objectX, objectY, imgLoader->getMapImage(firstImgID + objectID - 1), objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
			tree->setDestroyedState();
		}
		else if(objectClasses[objectID] == "AppleTreeStump")
		{
			//TODO: Currently, AppleTrees use only the full and empty state. Stump is not used. For now, the stump creates a full AppleTree
			new AppleTree(objectID, objectX, objectY, imgLoader->getMapImage(firstImgID + objectID - 2), imgLoader->getMapImage(firstImgID + objectID - 1), objectImg);
		}
		else if(objectClasses[objectID] == "Rock")
		{
			new Rock(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID+1));
		}
		else if(objectClasses[objectID] == "RockPieces")
		{
			Rock* rock = new Rock(objectID, objectX, objectY, imgLoader->getMapImage(firstImgID + objectID - 1), objectImg);
			rock->setDestroyedState();
		}
		else if (objectClasses[objectID] == "RockSpikes")
		{
			new RockSpikes(objectID, objectX, objectY, objectImg);
		}
		else if (objectClasses[objectID] == "GoldRock")
		{
			new GoldRock(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
		}
		else if (objectClasses[objectID] == "GoldRockPieces")
		{
			GoldRock* goldRock = new GoldRock(objectID, objectX, objectY, imgLoader->getMapImage(firstImgID + objectID - 1), objectImg);
			goldRock->setDestroyedState();
		}
		else if (objectClasses[objectID] == "Ice")
		{
			new Ice(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
		}
		else if (objectClasses[objectID] == "IceSpikes")
		{
			new Ice(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID - 1));
		}
		else if (objectClasses[objectID] == "IcePieces")
		{
			Ice* ice = new Ice(objectID, objectX, objectY, imgLoader->getMapImage(firstImgID + objectID - 1), objectImg);
			ice->setDestroyedState();
		}
		else if(objectClasses[objectID] == "Carrot")
		{
			new Carrot(objectID, objectX, objectY, objectImg);
		}
		else if(objectClasses[objectID] == "Pillar")
		{
			new Pillar(objectID, objectX, objectY, objectImg);
		}
		else if(objectClasses[objectID] == "RuinStatue")
		{
			new RuinStatue(objectID, objectX, objectY, objectImg);
		}
		else if (objectClasses[objectID] == "EasterHead" || objectClasses[objectID] == "EasterHeadDestroyed")
		{
			new EasterHead(objectID, objectX, objectY, objectImg);
		}
		else if (objectClasses[objectID] == "Cactus")
		{
			new Cactus(objectID, objectX, objectY, objectImg);
		}
		else if (objectClasses[objectID] == "InteractableCactus")
		{
			new InteractableCactus(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
		}
		else if(objectClasses[objectID] == "Fish")
		{
			new Fish(objectID, objectX, objectY, objectImg);
		}
		else if(objectClasses[objectID] == "SnowTree")
		{
			new SnowTree(objectID, objectX, objectY, objectImg);
		}
		processedObjects++;
		tempPercentage = startLoadPercentage + ((processedObjects / totalObjects) * loadWeight);
		if (tempPercentage != this->loadPercentage) {
			this->setPercentage(tempPercentage);
		}
	}
}

void MapLoader::createSpawnPoints(Value& spawnpoints)
{
	double startLoadPercentage = loadPercentage;
	double loadWeight = 10;
	double totalSpawnpoints = spawnpoints.Capacity();
	double processedSpawnpoints = 0;
	int tempPercentage = loadPercentage;
	loadStatus = "Creating spawnpoints.";

	for(int j = 0; j < spawnpoints.Capacity(); j++)
	{
		Value& object = spawnpoints[j];
		Value& properties = object["properties"];

		string spawnType = properties["SpawnType"].GetString();
		if(spawnType == "player")
		{
			startPosX = object["x"].GetDouble();
			startPosY = object["y"].GetDouble();
		}
		else
		{
			new Spawnpoint(0, object["x"].GetDouble(), object["y"].GetDouble(), spawnType, 3, 400);
		}
		processedSpawnpoints++;
		tempPercentage = startLoadPercentage + ((processedSpawnpoints / totalSpawnpoints) * loadWeight);
		if (tempPercentage != this->loadPercentage) {
			this->setPercentage(tempPercentage);
		}
	}



}

int MapLoader::getMapHeight()
{
	return mapHeight;
}

int MapLoader::getMapWidth()
{
	return mapWidth;
}

int MapLoader::getStartPosX()
{
	return startPosX;
}

int MapLoader::getStartPosY()
{
	return startPosY;
}

int MapLoader::getLoadPercentage()
{
	return loadPercentage;
}

string MapLoader::getLoadStatus()
{
	return loadStatus;
}

MapLoader::~MapLoader()
{
}
