#include "header_loader.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Button.h"
#include "GameStateManager.h"
#include <iostream>
#include <SDL_ttf.h>

MenuState MenuState::m_MenuState;

MenuState::MenuState(void)
{
}

void MenuState::init(GameStateManager *gsm) {
	backgroundTexture = IMG_LoadTexture(gsm->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures/campfire.jpg").c_str());
	if (backgroundTexture == NULL)
	{
		std::cout << "Error loading startmenu background" << std::endl << "Error 2" << std::endl;
		system("pause");
	}
	this->gsm = gsm;
	align();
	//Create Buttons
	if (buttons.size() < 2) {
	buttons.push_back(new PlayButton(gsm));
	buttons.push_back(new ExitButton(gsm));
	}

	//align buttons
	for (int i = 0; i < buttons.size(); i++) {
		buttons.at(i)->align(buttons.size() - i, buttons.size());
	}

	//Bermuda text
	TTF_Font* staryDarzyLarge = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 80);
	SDL_Color white = { 255, 255, 255 };
	std::string bermudaMessage = "Bermuda";
	SDL_Surface* bermudaMessageSurface = TTF_RenderText_Blended(staryDarzyLarge, bermudaMessage.c_str(), white);
	bermudaTextTexture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), bermudaMessageSurface);

	bermudaTextRect.x = ((int)ScreenWidth - bermudaMessageSurface->w) / 2;
	bermudaTextRect.y = 50;
	bermudaTextRect.h = bermudaMessageSurface->h;
	bermudaTextRect.w = bermudaMessageSurface->w;

	SoundLoader* soundLoader = gsm->getSoundLoader();
	soundLoader->playMenuMusic();
	//SoundLoader::Instance()->playMenuMusic();

	SDL_FreeSurface(bermudaMessageSurface);
	TTF_CloseFont(staryDarzyLarge);
}

void MenuState::align()
{
	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = ScreenWidth;
	backgroundRect.h = ScreenHeight;
}

void MenuState::handleEvents(SDL_Event mainEvent) {
	int x, y;
	SDL_GetMouseState(&x, &y);
	switch(mainEvent.type) {
	case SDL_KEYDOWN:
		switch(mainEvent.key.keysym.sym) {
		case SDLK_SPACE:
			this->gsm->changeGameState(PlayState::Instance());
			break;
		}
		break;
	case SDL_MOUSEMOTION: 
		for (int i = 0; i < buttons.size(); i++) {
			buttons.at(i)->hover(x, y, gsm);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT) {
			for (int i = 0; i < buttons.size(); i++) {
				buttons.at(i)->clicked(x, y, gsm);
			}
		}
		break;
	}

}

void MenuState::draw() {
	SDL_RenderCopy(gsm->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);
	SDL_RenderCopy(gsm->sdlInitializer->getRenderer(), bermudaTextTexture, NULL, &bermudaTextRect);
	for (int i = 0; i < buttons.size(); i++) {
		buttons.at(i)->draw( gsm);
	}
}

void MenuState::update(double dt)
{
	
}

void MenuState::pause() {

}

void MenuState::resume() {

}

void MenuState::cleanup() {
	SDL_FreeSurface(bg);
	SDL_DestroyTexture(backgroundTexture);

	for (int i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
}

MenuState::~MenuState(void)
{
	cleanup();
}
