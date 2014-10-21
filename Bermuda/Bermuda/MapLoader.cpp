#include "MapLoader.h"
#include "Tile.h"
#include "Tree.h"
#include "Rock.h"
#include "CollidableTile.h"

#include <rapidjson/stringbuffer.h>
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>
#include <math.h>


MapLoader::MapLoader(GameStateManager* gsm, MainEntityContainer* mec)
	: gsm(gsm), mec(mec), imgLoader(gsm->getImageLoader()), chunkSize(300)
{
}

void MapLoader::loadMap()
{
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
	while (getline(stream, line)) {
		json += line;
	}

	//Close stream.
	stream.close();

	//Parse JSON string into DOM.
	Document d;
	d.Parse(json.c_str());

	extractMapInfo(d);
}

void MapLoader::extractMapInfo(Document& d)
{
	//Get general map information
	int mapTileHeight = d["height"].GetInt();
	int mapTileWidth = d["width"].GetInt();
	int tileHeight = d["tileheight"].GetInt();
	int tileWidth = d["tilewidth"].GetInt();

	mapHeight = mapTileHeight * tileHeight;
	mapWidth = mapTileWidth * tileWidth;

	//Set the containers
	mec->initContainerSizes(floor(mapHeight/chunkSize) +1, floor(mapWidth/chunkSize) +1);

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
	}
}

void MapLoader::createTileSets(Value& tilesets)
{
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
	}
}

void MapLoader::createTiles(Value& tiles, int mapTileHeight, int mapTileWidth, int tileHeight, int tileWidth)
{
	for (int y = 0; y < mapTileHeight; y++)
	{
		for (int x = 0; x < mapTileWidth; x++)
		{
			int tileID = tiles[(y*mapTileWidth)+x].GetInt();

			if(find(collisionVector.begin(), collisionVector.end(), tileID) != collisionVector.end())
			{
				//Tile is in collision vector. Create collisionTile.
				CollidableTile* tile = new CollidableTile(tileID, chunkSize, mec, x*tileWidth, y*tileHeight, imgLoader->getMapImage(tileID));
			}
			else
			{
				//Tile is not in collision vector. Creating normal tile.
				Tile* tile = new Tile(tileID, chunkSize, mec, x*tileWidth, y*tileHeight, imgLoader->getMapImage(tileID));				
			}
		}
	}
}

void MapLoader::createObjects(Value& objects)
{
	//Possibly use this to create objects from strings
	/*map_type map;
	map["DerivedA"] = &createInstance<DerivedA>;
	map["DerivedB"] = &createInstance<DerivedB>;
	//And then you can do
	return map[some_string]();*/
	
	for(int j = 0; j < objects.Capacity(); j++)
	{
		Entity* e = nullptr;

		Value& object = objects[j];
		int objectID = object["gid"].GetInt();
		Image* objectImg = imgLoader->getMapImage(objectID);
		double objectX = object["x"].GetDouble();
		double objectY = object["y"].GetDouble() - objectImg->getHeight(); // -getHeight() Because all 'tiled' objects use bottom left for image positioning;

		//TODO: Any better way to do this?
		if(objectClasses[objectID] == "Tree")
		{
			e = new Tree(objectID, chunkSize, mec, objectX, objectY, objectImg, imgLoader->getMapImage(objectID+1));
		}
		else if(objectClasses[objectID] == "TreeStump")
		{
			e = new Tree(objectID, chunkSize, mec, objectX, objectY, imgLoader->getMapImage(objectID-1), objectImg);
			//TODO: Set tree in his 'stump' state. (If we want to allow placing stumps directly in the 'tiled' map.)
		}
		else if(objectClasses[objectID] == "Rock")
		{
			e = new Rock(objectID, chunkSize, mec, objectX, objectY, objectImg, imgLoader->getMapImage(objectID+1));
			//Create rock object
			//Rock also has 2 images. Big rock and destroyed rock. 
		}
		else if(objectClasses[objectID] == "RockPieces")
		{
			e = new Rock(objectID, chunkSize, mec, objectX, objectY, imgLoader->getMapImage(objectID-1), objectImg);
			//Create destroyed rock object
		}
	}
}

void MapLoader::createSpawnPoints(Value& spawnpoints)
{
	//TODO: Create spawnpoint objects
	for(int j = 0; j < spawnpoints.Capacity(); j++)
	{
		Value& object = spawnpoints[j];
		cout << "- x: " << object["x"].GetInt() << " ";
		cout << "y: " << object["y"].GetInt() << " ";
		cout << "type: " << object["type"].GetString() << endl;
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

int MapLoader::getChunkSize()
{
	return chunkSize;
}

MapLoader::~MapLoader()
{
}
