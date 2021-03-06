#pragma once
#include "BaseScreen.h"
#include "BaseHelpScreen.h"
#include "BaseButton.h"

class MenuHelpScreen :
	public BaseScreen
{
private:
	//variables
	SDL_Texture* firstTexture;
	SDL_Rect firstRect;
	SDL_Rect secRect;
	SDL_Texture* secTexture;
	std::vector<BaseButton*> buttons;

	BaseHelpScreen* curWindow;
	BaseHelpScreen* movementScreen;
	BaseHelpScreen* cutTreeScreen;
	BaseHelpScreen* cutCactusScreen;
	BaseHelpScreen* fishScreen;
	BaseHelpScreen* pickAppleScreen;
	BaseHelpScreen* pickCarrotScreen;
	BaseHelpScreen* mineGoldScreen;
	BaseHelpScreen* mineIceScreen;
	BaseHelpScreen* mineRockScreen;
	BaseHelpScreen* foodAndWaterScreen;
	BaseHelpScreen* timeScreen;
	BaseHelpScreen* craftingScreen;
	BaseHelpScreen* fightingScreen;


	//methodes
	void init();
	void cleanup();
	void setBackground();

public:
	//methodes
	void resetButtons();
	void handleEvents(SDL_Event);
	void draw();

	//Methodes		Screens
	void setCurWindow(BaseHelpScreen* curwindow);
	BaseHelpScreen* getMovementScr();
	BaseHelpScreen* getCutTreeScr();
	BaseHelpScreen* getCutCactusScr();
	BaseHelpScreen* getFishScr();
	BaseHelpScreen* getPickAppleScr();
	BaseHelpScreen* getPickCarrotScr();
	BaseHelpScreen* getMineGoldScr();
	BaseHelpScreen* getMineIceScr();
	BaseHelpScreen* getMineRockScr();
	BaseHelpScreen* getFoodAndWaterScr();
	BaseHelpScreen* getTimeScr();
	BaseHelpScreen* getCraftingScr();
	BaseHelpScreen* getFightingScr();

	//constructors destructors
	MenuHelpScreen();
	virtual ~MenuHelpScreen();
};

