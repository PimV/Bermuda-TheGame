#include "SaveFile.h"
#include "header_loader.h"
#include "PlayState.h"
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace rapidjson;


SaveFile::SaveFile()
{
	this->init();
}

void SaveFile::init()
{
	this->currentSaveFile = "";
	this->saveLoadPossible = true;

	//Create save-game directory if it does not exist.
	if (!CreateDirectory(SAVEPATH.c_str(), NULL) &&
		ERROR_ALREADY_EXISTS != GetLastError())
	{
		// Failed to create directory.
		this->saveLoadPossible = false;
	}

	//Set current save file name to the first new available name.
	int saveNumber = 0;
	std::ifstream f;
	while (f.good()) 
	{
		f.close();
		this->currentSaveFile = "Game" + std::to_string(saveNumber) + ".json";
		f.open(SAVEPATH + this->currentSaveFile);
		saveNumber++;
	}
	f.close();
}

void SaveFile::changeCurrentSaveFile(std::string fileName)
{
	this->currentSaveFile = fileName;
}

void SaveFile::loadGame()
{
	this->loadGame(this->currentSaveFile);
}

void SaveFile::loadGame(std::string fileName)
{
	std::cout << "loading..." << std::endl;
	this->currentSaveFile = fileName;

	//Create file stream.
	std::ifstream stream(SAVEPATH + this->currentSaveFile);
	if (!stream.is_open())
	{
		std::cout << "Could not load save file. File " + this->currentSaveFile + " could not be found!" << std::endl;
		return;
	}

	//Read entire file into a string.
	std::string json;
	std::string line;
	while (getline(stream, line))
	{
		json += line;
	}
	stream.close();

	//Parse JSON string into DOM.
	Document d;
	d.Parse(json.c_str());

	std::cout << json << std::endl;
	//TODO: Change entities based on saved data.
	//Value& tilesets = d["tilesets"];

	GameTimer::Instance()->setGameTime(d["gametime"].GetDouble());

	//Player position, health, thirst & hunger
	PlayState::Instance()->getPlayer()->setPosition(d["player"]["x"].GetDouble(), d["player"]["y"].GetDouble());
	PlayState::Instance()->getPlayer()->setHealth(d["player"]["health"].GetInt());
	PlayState::Instance()->getPlayer()->setThirst(d["player"]["thirst"].GetInt());
	PlayState::Instance()->getPlayer()->setHunger(d["player"]["hunger"].GetInt());

	//Achievement stats
	vector<int> stats;
	for (int i = 0; i < d["stats"].Size(); i++)
	{
		stats.push_back(d["stats"][i].GetInt());
	}
	PlayState::Instance()->getPlayer()->getStatusTracker()->setAllStats(stats);

	std::cout << "done" << std::endl;
}

void SaveFile::saveGame()
{
	this->saveGame(this->currentSaveFile);
}

void SaveFile::saveGame(std::string fileName)
{
	std::cout << "saving..." << std::endl;

	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();

	writer.String("player");
	writer.StartObject();
	writer.String("x");
	writer.Double(PlayState::Instance()->getPlayer()->getX());
	writer.String("y");
	writer.Double(PlayState::Instance()->getPlayer()->getY());
	writer.String("health");
	writer.Int(PlayState::Instance()->getPlayer()->getHealth());
	writer.String("thirst");
	writer.Int(PlayState::Instance()->getPlayer()->getThirst());
	writer.String("hunger");
	writer.Int(PlayState::Instance()->getPlayer()->getHunger());
	writer.EndObject();

	writer.String("stats");
	writer.StartArray();
	for (Achievement* achievement : PlayState::Instance()->getPlayer()->getStatusTracker()->getAllAchievements())
	{
		writer.Int(achievement->getAmount());
	}
	writer.EndArray();

	writer.String("gametime");
	writer.Double(GameTimer::Instance()->getGameTime());

	writer.EndObject();

	std::ofstream stream(SAVEPATH + this->currentSaveFile);
	if (!stream.is_open())
	{
		std::cout << "Could not save file. File " + this->currentSaveFile + " could not be found!" << std::endl;
		return;
	}
	stream << s.GetString();
	stream.close();

	std::cout << s.GetString() << std::endl;
}

SaveFile::~SaveFile()
{
}
