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

	tempScreen = new BaseHelpScreen(tempRect.w);
	setCurWindow(tempScreen);

//	SDL_FillRect(s, NULL, SDL_MapRGB(s->format, 99, 232, 72));
//	temp2Texture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), s);
//	SDL_FreeSurface(s);
//
//	temp2Rect.h = ScreenHeight;
//	temp2Rect.w = (ScreenWidth / 5) * 4;
//	temp2Rect.x = tempRect.w;
//	temp2Rect.y = 0;
}

void MenuHelpScreen::setCurWindow(BaseHelpScreen* curwindow)
{
	curWindow = curwindow;
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
//	SDL_RenderCopy(renderer, temp2Texture, NULL, &temp2Rect);
	curWindow->draw();
}

void MenuHelpScreen::cleanup()
{
	SDL_DestroyTexture(tempTexture);
	delete tempScreen;
}

MenuHelpScreen::~MenuHelpScreen()
{
	cleanup();
}
