#include "GameSaver.h"
#include "header_loader.h"
#include "PlayState.h"
#include "Item.h"
#include "Items.h"
#include "Achievement.h"
#include "ItemFactory.h"
#include <vector>
#include <Windows.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace rapidjson;


GameSaver::GameSaver()
{
	this->init();
}

void GameSaver::init()
{
	this->currentSaveFile = "";

	//Create save-game directory if it does not exist.
	if (!CreateDirectory(SAVEPATH.c_str(), NULL) &&
		ERROR_ALREADY_EXISTS != GetLastError())
	{
		// Failed to create directory.
		std::cout << "Could not create save file directory. ("+SAVEPATH+")" << std::endl;
		return;
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

void GameSaver::changeCurrentSaveFile(std::string fileName)
{
	this->currentSaveFile = fileName;
}

void GameSaver::loadGame()
{
	this->loadGame(this->currentSaveFile);
}

void GameSaver::loadGame(std::string fileName)
{
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

	//Gametime
	GameTimer::Instance()->setGameTime(d["gametime"].GetDouble());

	//Player stats
	PlayState::Instance()->getPlayer()->setPosition(d["player"]["x"].GetDouble(), d["player"]["y"].GetDouble());
	PlayState::Instance()->getPlayer()->setHealth(d["player"]["health"].GetInt());
	PlayState::Instance()->getPlayer()->setThirst(d["player"]["thirst"].GetInt());
	PlayState::Instance()->getPlayer()->setHunger(d["player"]["hunger"].GetInt());

	//Inventory
	PlayState::Instance()->getPlayer()->getInventory()->clearInventory();
	for (size_t i = 0; i < d["inventory"].Size(); i++)
	{
		Item* item = ItemFactory::Instance()->createItem(static_cast<Items>(d["inventory"][i]["id"].GetInt()));
		item->setStackSize(d["inventory"][i]["amount"].GetInt());
		PlayState::Instance()->getPlayer()->getInventory()->addItem(item);
	}

	//Achievements
	vector<int> stats;
	for (size_t i = 0; i < d["achievements"].Size(); i++)
	{
		stats.push_back(d["achievements"][i].GetInt());
	}
	PlayState::Instance()->getPlayer()->getStatusTracker()->setAllStats(stats);
}

void GameSaver::saveGame()
{
	this->saveGame(this->currentSaveFile);
}

void GameSaver::saveGame(std::string fileName)
{
	StringBuffer s;
	Writer<StringBuffer> writer(s);

	writer.StartObject();

	//Gametime
	writer.String("gametime");
	writer.Double(GameTimer::Instance()->getGameTime());

	//Player stats
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

	//Inventory
	writer.String("inventory");
	writer.StartArray();
	for (Item* item : PlayState::Instance()->getPlayer()->getInventory()->getItems())
	{
		writer.StartObject();
		writer.String("id");
		writer.Int(item->getId());
		writer.String("amount");
		writer.Int(item->getStackSize());
		writer.EndObject();
	}
	writer.EndArray();

	//Achievements
	writer.String("achievements");
	writer.StartArray();
	for (Achievement* achievement : PlayState::Instance()->getPlayer()->getStatusTracker()->getAllAchievements())
	{
		writer.Int(achievement->getAmount());
	}
	writer.EndArray();

	writer.EndObject();

	//Save file
	std::ofstream stream(SAVEPATH + this->currentSaveFile);
	if (!stream.is_open())
	{
		std::cout << "Could not save file. File " + this->currentSaveFile + " could not be found!" << std::endl;
		return;
	}
	stream << s.GetString();
	stream.close();
}

GameSaver::~GameSaver()
{
}
