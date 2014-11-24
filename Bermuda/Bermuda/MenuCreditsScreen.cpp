#include "MenuCreditsScreen.h"
#include <SDL_image.h>
#include <iostream>
#include "MenuState.h"


MenuCreditsScreen::MenuCreditsScreen()
{
	init();
}

void MenuCreditsScreen::init()
{
	setBackground();
	setNames();
	createNameTextures();
	align();

}

void MenuCreditsScreen::setNames()
{
	names.push_back(std::string("Pim Verlangen"));
	names.push_back(std::string("Bas van den Heuvel"));
	names.push_back(std::string("Johan Beekers"));
	names.push_back(std::string("James Hay"));
	names.push_back(std::string("Roel Atteveld"));
	names.push_back(std::string("Sagar Gangabisoensingh"));
}

void MenuCreditsScreen::createNameTextures()
{
	TTF_Font* staryDarzyLarge = TTF_OpenFont((RESOURCEPATH + "fonts\\andyb.ttf").c_str(), 40);
	SDL_Color white = { 255, 255, 255 };

	for each (std::string var in names)
	{
		SDL_Surface* nameSurface = TTF_RenderText_Blended(staryDarzyLarge, var.c_str(), white);
		SDL_Texture* nameTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), nameSurface);
		SDL_Rect nameRect;
		nameRect.h = nameSurface->h;
		nameRect.w = nameSurface->w;

		nameTextures.push_back(nameTexture);
		nameRectangles.push_back(nameRect);

		//clear surfaces
		SDL_FreeSurface(nameSurface);
	}
	TTF_CloseFont(staryDarzyLarge);
}

void MenuCreditsScreen::align()
{
	int total = 0;
	for each (SDL_Rect var in nameRectangles)
	{
		total += var.h;
	}
	int minSur = ((int)ScreenHeight - total) / 2;

	for (size_t i = 0; i < nameRectangles.size(); i++)
	{
		nameRectangles.at(i).x = (ScreenWidth - nameRectangles.at(i).w) / 2;
		nameRectangles.at(i).y = minSur;
		minSur += nameRectangles.at(i).h;
	}
}

void MenuCreditsScreen::setBackground()
{
	//Bermuda text
	TTF_Font* staryDarzyLarge = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 80);
	SDL_Color white = { 255, 255, 255 };
	std::string bermudaMessage = "Bermuda";
	SDL_Surface* bermudaMessageSurface = TTF_RenderText_Blended(staryDarzyLarge, bermudaMessage.c_str(), white);
	bermudaTextTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), bermudaMessageSurface);

	bermudaTextRect.x = ((int)ScreenWidth - bermudaMessageSurface->w) / 2;
	bermudaTextRect.y = 50;
	bermudaTextRect.h = bermudaMessageSurface->h;
	bermudaTextRect.w = bermudaMessageSurface->w;

	//clearing surfaces
	SDL_FreeSurface(bermudaMessageSurface);
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

void MenuCreditsScreen::handleEvents(SDL_Event mainEvent)
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

void MenuCreditsScreen::draw()
{
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);
	//SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), bermudaTextTexture, NULL, &bermudaTextRect);
	
	for (size_t i = 0; i < nameTextures.size(); i++)
	{
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), nameTextures.at(i), NULL, &nameRectangles.at(i));
	}
}

void MenuCreditsScreen::cleanup()
{
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(bermudaTextTexture);
}

MenuCreditsScreen::~MenuCreditsScreen()
{
}
