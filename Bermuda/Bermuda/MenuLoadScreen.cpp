#include "MenuLoadScreen.h"
#include "MenuState.h"
#include <SDL_image.h>
#include "GameTimer.h"
#include "SavedGameButton.h"
#include "LoadButton.h"
#include "PlayState.h"

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>

using namespace rapidjson;


MenuLoadScreen::MenuLoadScreen()
{
	this->currentFileToLoad = "";
	readSavedGames();
	init();
}

void MenuLoadScreen::init()
{
	setBackground();

	BaseButton* returnButton = new BaseButton();
	returnButton->action = &BaseButton::menuMainScreenAction;
	returnButton->createButton("Return to main menu", 40, 0);
	returnButton->placeMidUnder(((ScreenWidth - returnButton->getWidth()) / 2), ScreenHeight - ScreenHeight/ 10);
	buttons.push_back(returnButton);

	int y = 50;
	//Saved game buttons
	for (std::pair<std::string, int> pair : this->savedGames)
	{
		SavedGameButton* button = new SavedGameButton(this, pair.first);
		button->createButton(pair.first.substr(0, pair.first.find_last_of('.')) + "     Days survived: " + std::to_string(pair.second), 24, 0);
		button->placeExactAt((ScreenWidth / 2) - (button->getWidth() / 2), y);
		savedGameButtons.push_back(button);		

		y += 30;

		if (y + 250 >= ScreenHeight)
		{
			break;
		}
	}

	y += 30;

	loadButton = new LoadButton(this);
	loadButton->createButton(" ", 40, 0);
	loadButton->placeExactAt((ScreenWidth / 2) - (loadButton->getWidth() / 2), y);
}

void MenuLoadScreen::setCurrentFileToLoad(std::string fileName)
{
	this->currentFileToLoad = fileName;
	this->loadButton->setNewButtonText("Load: " + fileName, 40, 0);
	this->loadButton->placeExactAt((ScreenWidth / 2) - (this->loadButton->getWidth() / 2), this->loadButton->getY());
}

void MenuLoadScreen::readSavedGames()
{
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	TCHAR patter[MAX_PATH];

	memset(patter, 0x00, MAX_PATH);
	_stprintf_s(patter, TEXT("%s\\*.json"), SAVEPATH.c_str());
	hFind = FindFirstFile(patter, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		printf("FindFirstFile failed (%d)\n", GetLastError());
	}
	else
	{
		do
		{
			//ignore current and parent directories
			if (_tcscmp(FindFileData.cFileName, TEXT(".")) == 0 || _tcscmp(FindFileData.cFileName, TEXT("..")) == 0)
				continue;

			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				//ignore directories
			}
			else
			{
				std::string fileName = FindFileData.cFileName;
				//std::string fileNameSplit = fileName.substr(0, fileName.find_last_of('.'));

				//Create file stream.
				std::ifstream stream(SAVEPATH + fileName);
				if (!stream.is_open())
				{
					std::cout << "Could not read save file. File " + fileName + " could not be found!" << std::endl;
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

				//Get amount of days survived
				int totalDays = d["days"].GetInt();

				//list the saved file
				this->savedGames[fileName] = totalDays;
			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}
}

void MenuLoadScreen::cleanup()
{
	SDL_DestroyTexture(backgroundTexture);
	for(BaseButton* var : buttons)
	{
		delete var;
	}
	buttons.clear();
}

void MenuLoadScreen::setBackground()
{
	backgroundTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures/campfire.jpg").c_str());
	if (backgroundTexture == NULL)
	{
		std::cout << "Error loading startmenu background" << std::endl << "Error 2" << std::endl;
		system("pause");
	}

	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = ScreenWidth;
	backgroundRect.h = ScreenHeight;
}


void MenuLoadScreen::resetButtons()
{
	for(BaseButton* var : buttons)
	{
		var->reset();
	}
}

void MenuLoadScreen::handleEvents(SDL_Event mainEvent)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch (mainEvent.type) {
	case SDL_KEYDOWN:
		switch (mainEvent.key.keysym.sym) {
		case SDLK_ESCAPE:
			MenuState::Instance()->setCurWindow(MenuState::Instance()->getMenuMainScreen());
			break;
		}
		break;
	case SDL_MOUSEMOTION:
		this->loadButton->hover(x, y);
		for (SavedGameButton* var : savedGameButtons)
		{
			var->hover(x, y);
		}
		for(BaseButton* var : buttons)
		{
			var->hover(x, y);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT)
		{
			if (this->loadButton->clicked(x, y))
			{
				if (this->currentFileToLoad != "")
				{
					this->loadCurrentFile();
					break;
				}
			}
			for (SavedGameButton* var : savedGameButtons)
			{
				if (var->clicked(x, y))
				{
					break;
				}
			}
			for(BaseButton* var : buttons)
			{
				if (var->clicked(x, y))
				{
					break;
				}
			}
		}
		break;
	}
}

void MenuLoadScreen::loadCurrentFile()
{
	std::cout << currentFileToLoad << std::endl;
	PlayState::Instance()->setFileToLoad(this->currentFileToLoad);
	GameStateManager::Instance()->changeGameState(PlayState::Instance());
	PlayState::Instance()->loadGame();
}

void MenuLoadScreen::draw()
{	
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);
	
	for(BaseButton* var : buttons)
	{
		var->draw();
	}


	for (SavedGameButton* var : savedGameButtons)
	{
		var->draw();
	}

	this->loadButton->draw();
}


MenuLoadScreen::~MenuLoadScreen()
{
}
