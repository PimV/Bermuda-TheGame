#include "MenuGraveyardScreen.h"
#include "MenuState.h"

MenuGraveyardScreen::MenuGraveyardScreen()
{
	init();
}

void MenuGraveyardScreen::init()
{
	setBackground();
}

void MenuGraveyardScreen::setBackground()
{
	//Bermuda text
	TTF_Font* staryDarzyLarge = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 60);
	SDL_Color white = { 255, 255, 255 };
	std::string graveyardMessage = "Graveyard";
	SDL_Surface* graveyardMessageSurface = TTF_RenderText_Blended(staryDarzyLarge, graveyardMessage.c_str(), white);
	graveyardTextTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), graveyardMessageSurface);

	graveyardTextRect.x = ((int)ScreenWidth - graveyardMessageSurface->w) / 2;
	graveyardTextRect.y = 50;
	graveyardTextRect.h = graveyardMessageSurface->h;
	graveyardTextRect.w = graveyardMessageSurface->w;

	//clearing surfaces
	SDL_FreeSurface(graveyardMessageSurface);
	TTF_CloseFont(staryDarzyLarge);

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

void MenuGraveyardScreen::resetButtons()
{
	for (BaseButton* var : buttons)
	{
		var->reset();
	}
}

void MenuGraveyardScreen::handleEvents(SDL_Event mainEvent)
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
		for (BaseButton* var : buttons)
		{
			var->hover(x, y);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT)
		{
			for (BaseButton* var : buttons)
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

void MenuGraveyardScreen::draw()
{
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), graveyardTextTexture, NULL, &graveyardTextRect);

	for (BaseButton* var : buttons)
	{
		var->draw();
	}
}

void MenuGraveyardScreen::cleanup()
{
	SDL_DestroyTexture(backgroundTexture);
	for (BaseButton* var : buttons)
	{
		delete var;
	}
	buttons.clear();
}

MenuGraveyardScreen::~MenuGraveyardScreen()
{
	cleanup();
}
