#include "SaveFile.h"
#include "header_loader.h"
#include <Windows.h>


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
}

void SaveFile::changeCurrentSaveFile(std::string fileName)
{

}

void SaveFile::loadGame()
{
	this->loadGame(this->currentSaveFile);
}

void SaveFile::loadGame(std::string fileName)
{


}

void SaveFile::saveGame()
{
	this->saveGame(this->currentSaveFile);
}

void SaveFile::saveGame(std::string fileName)
{

}

SaveFile::~SaveFile()
{
}
