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
	movementScreen->setPicture("HelpScreens/Movement.bmp");
	movementScreen->setText("Gebruik de pijltjes toetsen om rond te lopen");

	BaseButton* movementButton = new BaseButton;
	movementButton->createButton("movement", 20, 1);
	
	movementButton->placeExactAt(10, 10);

	buttons.push_back(movementButton);

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

void MenuHelpScreen::setBackground()
{

}

void MenuHelpScreen::resetButtons()
{

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

		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT)
		{

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
