#include "MapLoader.h"

#include <rapidjson/stringbuffer.h>
#include <fstream>
#include <string>
#include <iostream>


MapLoader::MapLoader()
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
		else
		{
			//Useless layer
		}
		cout << endl;
	}
}

void MapLoader::createTileSets(Value& tilesets)
{
	cout << "\nTilesets: " << endl;
	//TODO: Create texture loader class that loads tilesets and creates SDL_textures. 
	//This class should keep ID's with textures in a map.
	for(int i = 0; i < tilesets.Capacity(); i++)
	{
		Value& tileset = tilesets[i];
		string imgName = tileset["image"].GetString();
		int imgHeight = tileset["imageheight"].GetInt();
		int imgWidth = tileset["imagewidth"].GetInt();
		int firstId = tileset["firstgid"].GetInt();

		cout << imgName << endl;
		cout << "\timg height: " << imgHeight << endl;
		cout << "\timg width: " << imgWidth << endl;
		cout << "\tfirst ID: " << firstId << endl;

		if(tileset.HasMember("tileproperties"))
		{
			for(Value::ConstMemberIterator it=tileset["tileproperties"].MemberBegin(); it != tileset["tileproperties"].MemberEnd(); it++) {
				for(Value::ConstMemberIterator it2=tileset["tileproperties"][it->name].MemberBegin(); it2 != tileset["tileproperties"][it->name].MemberEnd(); it2++) {
					string name = it2->name.GetString();
					int objectID = firstId+stoi(it->name.GetString());
					if (name == "Type")
					{
						//TODO: for project, Add object ID to map with class types
						cout << "Add ID " << objectID << " to types map with type: " << it2->value.GetString() << endl;
					}
					else if (name == "Collision")
					{
						//TODO: for project, add tile ID's to array/vector of collision tiles
						cout << "Add ID " << it->name.GetString() << " to collision vector" << endl;
					}
				}
			}
		}
	}
}

void MapLoader::createTiles(Value& tiles, int mapTileHeight, int mapTileWidth, int tileHeight, int tileWidth)
{
	//TODO: for project, create tile objects
	for (int j = 0; j < mapTileHeight; j++)
	{
		for (int k = 0; k < mapTileWidth; k++)
		{
			cout << tiles[(j*mapTileWidth)+k].GetInt() << " | ";
		}
		cout << endl;
	}
}

void MapLoader::createObjects(Value& objects)
{
	//TODO: for project, create objects
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
	//TODO: for project, create spawnpoint objects
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
