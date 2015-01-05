#pragma once
#include <string>

class GameSaver
{
private:
	std::string currentSaveFile;
public:
	GameSaver();
	void init();
	void changeCurrentSaveFile(std::string fileName);
	void loadGame();
	void loadGame(std::string fileName);
	void saveGame();
	void saveGame(std::string fileName);
	virtual ~GameSaver();
};

