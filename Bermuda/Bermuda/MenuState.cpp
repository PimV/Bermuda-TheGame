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

//TODO: remove GSM
void MenuState::init(GameStateManager* gsm) {
	//Background
	backgroundTexture = IMG_LoadTexture(GameStateManager::Instance()->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures/campfire.jpg").c_str());
	if (backgroundTexture == NULL)
	{
		std::cout << "Error loading startmenu background" << std::endl << "Error 2" << std::endl;
		system("pause");
	}
	align();

	//Create Buttons
	if (buttons.size() < 2) {
		PlayButton* playButton = new PlayButton();
		ExitButton* exitButton = new ExitButton();

		playButton->placeAbove(exitButton);

		buttons.push_back(playButton);
		buttons.push_back(exitButton);
	}

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

	//soundloader
	SoundLoader::Instance()->playMenuMusic();

	//clearing surfaces
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
			GameStateManager::Instance()->changeGameState(PlayState::Instance());
			break;
		}
		break;
	case SDL_MOUSEMOTION: 
		for (size_t i = 0; i < buttons.size(); i++) {
			buttons.at(i)->hover(x, y);
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (mainEvent.button.button == SDL_BUTTON_LEFT) {
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

void MenuState::draw() {
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);
	SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), bermudaTextTexture, NULL, &bermudaTextRect);
	for (size_t i = 0; i < buttons.size(); i++) {
		buttons.at(i)->draw();
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
	SDL_DestroyTexture(backgroundTexture);

	for (size_t i = 0; i < buttons.size(); i++)
	{
		delete buttons[i];
	}
	buttons.clear();
}

MenuState::~MenuState(void)
{
	cleanup();
}
