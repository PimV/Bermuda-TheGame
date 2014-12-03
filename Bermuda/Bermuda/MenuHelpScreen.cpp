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
	SDL_Surface* s;
	s = SDL_CreateRGBSurface(0, ScreenWidth, ScreenWidth, 32, 0, 0, 0, 0);
	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 255, 251, 0));
	tempTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), s);

	tempRect.h = ScreenHeight;
	tempRect.w = (ScreenWidth / 5) * 1;
	tempRect.x = 0;
	tempRect.y = 0;

	movementScreen = new BaseHelpScreen(tempRect.w);
	movementScreen->setPicture("HelpScreens/movement.bmp");
	movementScreen->setText("Use the arrow keys to walk around");

	cutTreeScreen = new BaseHelpScreen(tempRect.w);
	cutTreeScreen->setPicture("HelpScreens/cutTree.bmp");
	cutTreeScreen->setText("Stand close to a tree, select the axe in your inventory and press spacebar to cut down the tree");

	BaseButton* movementButton = new BaseButton;
	movementButton->createButton("Movement", 30, 1);
	movementButton->action = &BaseButton::helpMovementScreenAction;

	BaseButton* cutTreeButton = new BaseButton;
	cutTreeButton->createButton("Cut down trees", 30, 1);
	cutTreeButton->action = &BaseButton::helpCutTreeScreenAction;
	
	movementButton->placeExactAt(10, 10);
	cutTreeButton->placeLeftUnderButton(movementButton);

	buttons.push_back(movementButton);
	buttons.push_back(cutTreeButton);

	for each (BaseButton* var in buttons)
	{
		var->setHelpScr(this);
	}

	setCurWindow(movementScreen);
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
	SDL_RenderCopy(renderer, tempTexture, NULL, &tempRect);
	for each (BaseButton* var in buttons)
	{
		var->draw();
	}
	curWindow->draw();
}

void MenuHelpScreen::cleanup()
{
	SDL_DestroyTexture(tempTexture);
	delete movementScreen;
}

MenuHelpScreen::~MenuHelpScreen()
{
	cleanup();
}
