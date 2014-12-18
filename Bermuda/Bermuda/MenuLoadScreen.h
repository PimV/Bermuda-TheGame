#pragma once
#include "basescreen.h"
#include "GameStateManager.h"
#include "BaseButton.h"
#include <map>

class SavedGameButton;
class LoadButton;

class MenuLoadScreen :
	public BaseScreen
{
private:
	SDL_Texture* backgroundTexture;
	SDL_Rect backgroundRect;

	std::vector<BaseButton*> buttons;
	std::vector<SavedGameButton*> savedGameButtons;

	LoadButton* loadButton;

	std::map<std::string, int> savedGames;

	std::string currentFileToLoad;

	void init();
	void readSavedGames();
	void cleanup();
	void setBackground();
	void loadCurrentFile();

public:
	void resetButtons();
	void handleEvents(SDL_Event);
	void draw();

	void setCurrentFileToLoad(std::string fileName);

	MenuLoadScreen();
	virtual ~MenuLoadScreen();
};

