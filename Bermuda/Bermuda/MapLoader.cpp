#include "MapLoader.h"
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;
using namespace rapidjson;

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

	//Get general map information
	int mapHeight = d["height"].GetInt();
	int mapWidth = d["width"].GetInt();
	int tileHeight = d["tileheight"].GetInt();
	int tileWidth = d["tilewidth"].GetInt();

	cout << "Map info:" << endl;
	cout << "Map width: " << mapWidth << endl;
	cout << "Map height: " << mapHeight << endl;
	cout << "Tile size: " << tileWidth << " x " << tileHeight << endl;
	
	cout << "\nTilesets: " << endl;
	//TODO: Create texture loader class that loads tilesets and creates SDL_textures. 
	//This class should keep ID's with textures in a map.
	for(int i = 0; i < d["tilesets"].Capacity(); i++)
	{
		Value& tileset = d["tilesets"][i];
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

	cout << "\nMap:" << endl;
	for(int i = 0; i < d["layers"].Capacity(); i++)
	{
		Value& layer = d["layers"][i];
		string layerName = layer["name"].GetString();
		
		cout << layerName << endl;
		if(layerName == "Tiles")
		{
			//TODO: for project, create tile objects
			for (int j = 0; j < mapHeight; j++)
			{
				for (int k = 0; k < mapWidth; k++)
				{
					cout << layer["data"][(j*mapWidth)+k].GetInt() << " | ";
				}
				cout << endl;
			}
		}
		else if (layerName == "Objects")
		{
			//TODO: for project, create objects
			for(int j = 0; j < layer["objects"].Capacity(); j++)
			{
				Value& object = layer["objects"][j];
				cout << "- Object ID : " << object["gid"].GetInt() << " ";
				cout << "x: " << object["x"].GetInt() << " ";
				cout << "y: " << object["y"].GetInt() << endl;
			}
			//Get the class type from map made during tileset reading
		}
		else if (layerName == "SpawnPoints")
		{
			//TODO: for project, create spawnpoint objects
			for(int j = 0; j < layer["objects"].Capacity(); j++)
			{
				Value& object = layer["objects"][j];
				cout << "- x: " << object["x"].GetInt() << " ";
				cout << "y: " << object["y"].GetInt() << " ";
				cout << "type: " << object["type"].GetString() << endl;
			}
		}
		else
		{
			//Useless layer
		}
		cout << endl;
	}
}

MapLoader::~MapLoader()
{
}
