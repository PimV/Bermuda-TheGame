#include "Graveyard.h"
#include <string>
#include <algorithm>
#include "header_loader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <Windows.h>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

Graveyard::Graveyard()
{
	if (!CreateDirectory(SAVEPATH.c_str(), NULL) &&
		ERROR_ALREADY_EXISTS != GetLastError())
	{
		// Failed to create directory.
		std::cout << "Could not create save file directory. (" + SAVEPATH + ")" << std::endl;
		return;
	}

	loadGraveyard();
}

void Graveyard::loadGraveyard()
{
	std::ifstream stream(SAVEPATH + "save.dat");

	if (!stream.is_open())
	{
		std::cerr << "Error opening file. File save.dat could not be found!" << std::endl;
		return;
	}

	std::string file;
	std::string line;
	while (std::getline(stream, line))
	{
		file += line;
	}
	stream.close();

	rapidjson::Document d;
	d.Parse(file.c_str());

	for (size_t i = 0; i < d["entry"].Size(); i++)
	{
		GraveyardEntry* entry = new GraveyardEntry;
		entry->character = d["entry"][i]["name"].GetString();
		entry->daysSurvived = d["entry"][i]["daysSurvived"].GetInt();
		entry->dayDied = d["entry"][i]["dayDied"].GetInt();
		entry->monthDied = d["entry"][i]["monthDied"].GetInt();
		entry->yearDied = d["entry"][i]["yearDied"].GetInt();
		addToGraveyard(entry);
	}
}

void Graveyard::saveGraveyard()
{
	rapidjson::StringBuffer s;
	rapidjson::Writer<rapidjson::StringBuffer> writer(s);

	writer.StartObject();
	writer.String("entry");
	writer.StartArray();
	for (GraveyardEntry* entry : graveyard)
	{
		writer.StartObject();
		writer.String("name");
		writer.String(entry->character.c_str());
		writer.String("daysSurvived");
		writer.Int(entry->daysSurvived);
		writer.String("dayDied");
		writer.Int(entry->dayDied);
		writer.String("monthDied");
		writer.Int(entry->monthDied);
		writer.String("yearDied");
		writer.Int(entry->yearDied);
		writer.EndObject();
	}
	writer.EndArray();
	writer.EndObject();

	std::ofstream stream(SAVEPATH + "save.dat");
	if (!stream.is_open())
	{
		std::cout << "Could not save file. File save.dat could not be found!" << std::endl;
		return;
	}
	stream << s.GetString();
	stream.close();
}

bool Graveyard::CompareEntries(const GraveyardEntry* left, const GraveyardEntry* right) {
	return left->daysSurvived > right->daysSurvived;
}

void Graveyard::addToGraveyard(GraveyardEntry* newEntry)
{
	if (graveyard.size() == 0)
	{
		graveyard.push_back(newEntry);
		return;
	}
	if (graveyard.back()->daysSurvived < newEntry->daysSurvived)
	{
		graveyard.push_back(newEntry);
		sort(graveyard.begin(), graveyard.end(), CompareEntries);
	}

	while (graveyard.size() > 10)
	{
		graveyard.pop_back();
	}
}

std::vector<GraveyardEntry*> Graveyard::getAllEntries()
{
	return this->graveyard;
}

Graveyard::~Graveyard()
{
	saveGraveyard();
	for (size_t i = 0; i < graveyard.size(); i++)
	{
		delete graveyard[i];
	}
	std::vector<GraveyardEntry*>().swap(graveyard); // clear and shrink vector.
}
