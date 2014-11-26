#include "MenuHelpScreen.h"
#include "MenuState.h"

MenuHelpScreen::MenuHelpScreen()
{
	init();
}

void MenuHelpScreen::init()
{

}

void MenuHelpScreen::cleanup()
{

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

}

MenuHelpScreen::~MenuHelpScreen()
{
}
