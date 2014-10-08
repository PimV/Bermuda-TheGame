#include "MapLoader.h"
#include "Tile.h"

#include <rapidjson/stringbuffer.h>
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>


MapLoader::MapLoader(GameStateManager* gsm, MainEntityContainer* mec)
	: gsm(gsm), mec(mec), imgLoader(gsm->getImageLoader())
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

	cout << "Map info:" << endl;
	cout << "Map width: " << mapTileWidth << endl;
	cout << "Map height: " << mapTileHeight << endl;
	cout << "Tile size: " << tileWidth << " x " << tileHeight << endl;
	
	Value& tilesets = d["tilesets"];
	createTileSets(tilesets);

	cout << "\nMap:" << endl;
	for(int i = 0; i < d["layers"].Capacity(); i++)
	{
		Value& layer = d["layers"][i];
		string layerName = layer["name"].GetString();
		
		cout << layerName << endl;
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
		// Ignore any other layers.
		cout << endl;
	}
}

void MapLoader::createTileSets(Value& tilesets)
{
	cout << "\nTilesets: " << endl;
	for(int i = 0; i < tilesets.Capacity(); i++)
	{
		Value& tileset = tilesets[i];
		string imgName = tileset["image"].GetString();
		int tileHeight = tileset["tileheight"].GetInt();
		int tileWidth = tileset["tilewidth"].GetInt();
		int firstId = tileset["firstgid"].GetInt();

		imgLoader->loadTileset(imgName, tileWidth, tileHeight);

		cout << imgName << endl;
		cout << "\ttile height: " << tileHeight << endl;
		cout << "\ttile width: " << tileWidth << endl;
		cout << "\tfirst ID: " << firstId << endl;

		if(tileset.HasMember("tileproperties"))
		{
			for(Value::ConstMemberIterator it=tileset["tileproperties"].MemberBegin(); it != tileset["tileproperties"].MemberEnd(); it++) {
				for(Value::ConstMemberIterator it2=tileset["tileproperties"][it->name].MemberBegin(); it2 != tileset["tileproperties"][it->name].MemberEnd(); it2++) {
					string name = it2->name.GetString();
					int objectID = firstId+stoi(it->name.GetString());
					if (name == "Type")
					{
						objectClasses[objectID] = it2->value.GetString();
						cout << "Add ID " << objectID << " to types map with type: " << it2->value.GetString() << endl;
					}
					else if (name == "Collision")
					{
						collisionVector.push_back(objectID);
						cout << "Add ID " << objectID << " to collision vector" << endl;
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
			
			Tile* tile = nullptr;
			if(find(collisionVector.begin(), collisionVector.end(), tileID) != collisionVector.end())
			{
				//Tile is in collision vector. Create collisionTile and add to collision behaviour collections.
				//TODO: create collision tile?
				tile = new Tile(tileID, imgLoader->getMapImage(tileID));
			}
			else
			{
				//Tile is not in collision vector. Creating normal tile.
				tile = new Tile(tileID, imgLoader->getMapImage(tileID));
			}
			tile->setHeight(tileHeight);
			tile->setWidth(tileWidth);
			tile->setX(x*tileWidth);
			tile->setY(y*tileHeight);
			//Camera* camera = new Camera(0, 100, 640, 480);
			//tile->draw(camera, gsm->sdlInitializer->getRenderer());
			//TODO: Put tile object in drawable container
			mec->getDrawableContainer()->push_back(tile);

			cout << tileID << " | ";
		}
		cout << endl;
	}
	//SDL_RenderPresent(gsm->sdlInitializer->getRenderer());
	//Sleep(10000);
}

void MapLoader::createObjects(Value& objects)
{
	/*
	//Possibly use this to create objects from strings
	map_type map;
	map["DerivedA"] = &createInstance<DerivedA>;
	map["DerivedB"] = &createInstance<DerivedB>;
	//And then you can do
	return map[some_string]();
	*/

	//TODO: Create objects
	for(int j = 0; j < objects.Capacity(); j++)
	{
		Value& object = objects[j];
		cout << "- Object ID : " << object["gid"].GetInt() << " ";
		cout << "x: " << object["x"].GetInt() << " ";
		cout << "y: " << object["y"].GetInt() << endl;
	}
	//Get the class type from map made during tileset reading
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

MapLoader::~MapLoader()
{
}
