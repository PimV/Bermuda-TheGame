#include "MenuHelpScreen.h"
#include "MenuState.h"

MenuHelpScreen::MenuHelpScreen()
{
	init();
}

void tempFunction()
{
	cout << "tempFunction" << endl; 
}


void MenuHelpScreen::init()
{
	firstRect.h = ScreenHeight +80;
	firstRect.w = (ScreenWidth / 5) * 1;
	firstRect.x = 0;
	firstRect.y = 0-40;
	secRect.h = ScreenHeight;
	secRect.w = (ScreenWidth / 5) * 4;
	secRect.x = firstRect.w;
	secRect.y = 0;

	movementScreen = new BaseHelpScreen(firstRect.w);
	movementScreen->setPicture("HelpScreens/movement.bmp");
	movementScreen->setText("Use the arrow keys to walk around.");

	cutTreeScreen = new BaseHelpScreen(firstRect.w);
	cutTreeScreen->setPicture("HelpScreens/cutTree.bmp");
	cutTreeScreen->setText("Stand close to a tree, select the axe in your inventory and press spacebar to cut down the tree.");

	BaseButton* movementButton = new BaseButton;
	movementButton->createButton("Movement", 30, 0);
	movementButton->action = &BaseButton::helpMovementScreenAction;
	movementButton->setHoverAction(true);

	BaseButton* cutTreeButton = new BaseButton;
	cutTreeButton->createButton("Cut down trees", 30, 0);
	cutTreeButton->action = &BaseButton::helpCutTreeScreenAction;
	cutTreeButton->setHoverAction(true);

	BaseButton* returnButton = new BaseButton;
	returnButton->createButton("Back to menu", 30, 0);
	returnButton->action = &BaseButton::menuMainScreenAction;
	
	movementButton->placeExactAt(10, 10);
	cutTreeButton->placeLeftUnderButton(movementButton);
	returnButton->placeLeftUnder(10, 10);

	buttons.push_back(movementButton);
	buttons.push_back(cutTreeButton);
	buttons.push_back(returnButton);

	for each (BaseButton* var in buttons)
	{
		var->setHelpScr(this);
	}

	setCurWindow(movementScreen);
	setBackground();
}

void MenuHelpScreen::setCurWindow(BaseHelpScreen* curwindow)
{
	curWindow = curwindow;
}

BaseHelpScreen* MenuHelpScreen::getMovementScr()
{
	return movementScreen;
}

BaseHelpScreen* MenuHelpScreen::getCutTreeScr()
{
	return cutTreeScreen;
}

void MenuHelpScreen::setBackground()
{
	firstTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "single-inv-item.png").c_str());
	secTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures\\UltraJungle9.jpg").c_str());
}

void MenuHelpScreen::resetButtons()
{
	for each (BaseButton* var in buttons)
	{
		var->reset();
	}
}

void MenuHelpScreen::handleEvents(SDL_Event mainEvent)
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
		for (size_t i = 0; i < buttons.size(); i++) {
			buttons.at(i)->hover(x, y);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT)
		{
			for (size_t i = 0; i < buttons.size(); i++) {
				if (buttons.at(i)->clicked(x, y))
				{
					break;
				}
			}
		}
		break;
	}
}

void MenuHelpScreen::draw()
{
	SDL_Renderer* renderer = GameStateManager::Instance()->sdlInitializer->getRenderer();
	SDL_RenderCopy(renderer, firstTexture, NULL, &firstRect);
	SDL_RenderCopy(renderer, secTexture, NULL, &secRect);
	for each (BaseButton* var in buttons)
	{
		var->draw();
	}
	curWindow->draw();
}

void MenuHelpScreen::cleanup()
{
	SDL_DestroyTexture(firstTexture);
	SDL_DestroyTexture(secTexture);
	delete movementScreen;
	delete cutTreeScreen;
	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
}

MenuHelpScreen::~MenuHelpScreen()
{
	cleanup();
}
