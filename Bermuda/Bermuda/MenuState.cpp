#include "header_loader.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Button.h"
#include "GameStateManager.h"
#include <iostream>

MenuState MenuState::m_MenuState;

MenuState::MenuState(void)
{
}

void MenuState::init(GameStateManager *gsm) {
	backgroundTexture = IMG_LoadTexture(gsm->sdlInitializer->getRenderer(), "Textures/green.bmp");
	if (backgroundTexture == NULL)
	{
		std::cout << "Error loading startmenu background" << std::endl << "Error 2" << std::endl;
		system("pause");
	}
	this->gsm = gsm;
	align();
	//Create Buttons
	buttons.push_back(new PlayButton(gsm));
	buttons.push_back(new ExitButton(gsm));
	//playButton = new PlayButton(gsm);
	//exitButton = new ExitButton(gsm);
	for (int i = 0; i < buttons.size(); i++) {
		buttons.at(i)->align(buttons.size() - i, buttons.size());
	}

	SoundLoader* soundLoader = gsm->getSoundLoader();
	soundLoader->playMenuMusic();

	//playButton->align(1, totalButtons);
	//exitButton->align(0, totalButtons);
}

void MenuState::align()
{
	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = ScreenWidth;
	backgroundRect.h = ScreenHeight;
}

void MenuState::cleanup() {
	SDL_FreeSurface(bg);
}

void MenuState::pause() {

}

void MenuState::resume() {

}


void MenuState::handleEvents() {
	SDL_Event mainEvent;

	if (SDL_PollEvent(&mainEvent)) {
		int x, y;
		SDL_GetMouseState(&x, &y);
		switch(mainEvent.type) {
		case SDL_QUIT:
	
			this->gsm->quit();
			break;

		case SDL_KEYDOWN:
			switch(mainEvent.key.keysym.sym) {
			case SDLK_SPACE:
				this->gsm->changeGameState(PlayState::Instance());
				break;
			case SDLK_ESCAPE:
				this->gsm->quit();
				break;
			}
			break;
		case SDL_MOUSEMOTION: 
			for (int i = 0; i < buttons.size(); i++) {
				buttons.at(i)->hover(x, y, gsm);
			}
			//playButton->hover(x, y, gsm);
			//exitButton->hover(x, y, gsm);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (mainEvent.button.button == SDL_BUTTON_LEFT) {
				for (int i = 0; i < buttons.size(); i++) {
					buttons.at(i)->clicked(x, y, gsm);
				}
				//playButton->clicked(x, y, gsm);
				//exitButton->clicked(x, y, gsm);
			}
			break;
		}
	}
}

void MenuState::update(double dt) {
	//std::cout << "Pim rocks " << counter <<  std::endl;
}

void MenuState::draw() {
	gsm->sdlInitializer->clearScreen();
	SDL_RenderCopy(gsm->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);
	for (int i = 0; i < buttons.size(); i++) {
		buttons.at(i)->draw( gsm);
	}
	//playButton->draw(gsm);
	//exitButton->draw(gsm);
	gsm->sdlInitializer->drawScreen();

	
}



MenuState::~MenuState(void)
{
	SDL_DestroyTexture(backgroundTexture);
	delete playButton;
	delete exitButton;
}
