#pragma once
#include <string>

class SaveFile
{
private:
	std::string currentSaveFile;
	bool saveLoadPossible;
public:
	SaveFile();
	void init();
	void changeCurrentSaveFile(std::string fileName);
	void loadGame();
	void loadGame(std::string fileName);
	void saveGame();
	void saveGame(std::string fileName);
	virtual ~SaveFile();
};

