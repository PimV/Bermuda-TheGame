#pragma once
#include <string>

class SaveFile
{
private:
	std::string currentSaveFile;
public:
	SaveFile();
	void changeCurrentSaveFile(std::string fileName);
	void loadGame();
	void loadGame(std::string fileName);
	void saveGame();
	void saveGame(std::string fileName);
	virtual ~SaveFile();
};

