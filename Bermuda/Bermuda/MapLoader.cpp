#include "MapLoader.h"
#include "Tile.h"
#include "Tree.h"
#include "TreePine.h"
#include "TreeRound.h"
#include "AppleTree.h"
#include "Rock.h"
#include "RockSpikes.h"
#include "GoldRock.h"
#include "Ice.h"
#include "IceSpikes.h"
#include "IceRock.h"
#include "Carrot.h"
#include "Fish.h"
#include "Pillar.h"
#include "RuinStatue.h"
#include "EasterHead.h"
#include "Cactus.h"
#include "SnowTree.h"
#include "InteractableCactus.h"
#include "InteractableCactusBig.h"
#include "InteractableCactusSmall.h"
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

	for(size_t i = 0; i < d["layers"].Size(); i++)
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
	double totalTilesets = tilesets.Size();
	double processedTilesets = 0;
	int tempPercentage = loadPercentage;
	loadStatus = "Loading tilesets.";

	for(size_t i = 0; i < tilesets.Size(); i++)
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
	double startLoadPercentage = loadPercentage;
	double loadWeight = 20;
	double totalObjects = objects.Size();
	double processedObjects = 0;
	int tempPercentage = loadPercentage;
	loadStatus = "Creating objects.";

	for(size_t j = 0; j < objects.Size(); j++)
	{

		Value& object = objects[j];
		int objectID = object["gid"].GetInt();
		Image* objectImg = imgLoader->getMapImage(firstImgID + objectID);
		double objectX = object["x"].GetDouble();
		double objectY = object["y"].GetDouble() - objectImg->getHeight(); // -getHeight() Because all 'tiled' objects use bottom left for image positioning;

		//TODO: Any better way to do this?
		if(objectClasses[objectID] == "RoundTree")
		{
			new TreeRound(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
		}
		else if(objectClasses[objectID] == "PineTree")
		{
			new TreePine(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
		}
		else if(objectClasses[objectID] == "RoundTreeStump")
		{
			Tree* tree = new TreeRound(objectID, objectX, objectY, imgLoader->getMapImage(firstImgID + objectID - 1), objectImg);
			tree->setDestroyedState();
		}
		else if(objectClasses[objectID] == "PineTreeStump")
		{
			Tree* tree = new TreePine(objectID, objectX, objectY, imgLoader->getMapImage(firstImgID + objectID - 1), objectImg);
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
			new IceRock(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
		}
		else if (objectClasses[objectID] == "IceSpikes")
		{
			new IceSpikes(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID - 1));
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
		else if (objectClasses[objectID] == "BigInteractableCactus")
		{
			new InteractableCactusBig(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
		}
		else if (objectClasses[objectID] == "SmallInteractableCactus")
		{
			new InteractableCactusSmall(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
		}
		else if (objectClasses[objectID] == "BigCactusStump")
		{
			InteractableCactusBig* cactus = new InteractableCactusBig(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
			cactus->setDestroyedState();
		}
		else if (objectClasses[objectID] == "SmallCactusStump")
		{
			InteractableCactusSmall* cactus = new  InteractableCactusSmall(objectID, objectX, objectY, objectImg, imgLoader->getMapImage(firstImgID + objectID + 1));
			cactus->setDestroyedState();
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
	double totalSpawnpoints = spawnpoints.Size();
	double processedSpawnpoints = 0;
	int tempPercentage = loadPercentage;
	loadStatus = "Creating spawnpoints.";

	for(size_t j = 0; j < spawnpoints.Size(); j++)
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
