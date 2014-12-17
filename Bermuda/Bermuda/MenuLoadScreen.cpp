#include "MenuLoadScreen.h"
#include "MenuState.h"
#include <SDL_image.h>
#include <iostream>

#include <windows.h>
#include <tchar.h>
#include <stdio.h>
MenuLoadScreen::MenuLoadScreen()
{
	init();
	readSavedGames();
}

void MenuLoadScreen::init()
{
	setBackground();

	BaseButton* returnButton = new BaseButton();
	returnButton->action = &BaseButton::menuMainScreenAction;
	returnButton->createButton("Return to main menu", 40, 0);
	returnButton->placeMidUnder(((ScreenWidth - returnButton->getWidth()) / 2), ScreenHeight - ScreenHeight/ 10);
	buttons.push_back(returnButton);
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
				//list the Files
				this->savedGames.push_back(FindFileData.cFileName);
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
		for(BaseButton* var : buttons)
		{
			var->hover(x, y);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT)
		{
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

void MenuLoadScreen::draw()
{	
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);
	
	for(BaseButton* var : buttons)
	{
		var->draw();
	}
}


MenuLoadScreen::~MenuLoadScreen()
{
}
