#include "header_loader.h"
#include "MenuState.h"
#include "PlayState.h"
#include "Button.h"
#include "GameStateManager.h"
#include <iostream>

MenuState MenuState::m_MenuState;

MenuState::MenuState(void)
{
	counter = 0;
}

void MenuState::init() {
	SDL_Surface* temp = SDL_LoadBMP("menustate.bmp");

	bg = SDL_ConvertSurfaceFormat(temp, SDL_PIXELFORMAT_UNKNOWN, 0);

	SDL_FreeSurface(temp);
}

void MenuState::cleanup() {
	SDL_FreeSurface(bg);
}

void MenuState::pause() {

}

void MenuState::resume() {

}


void MenuState::handleEvents( GameStateManager *gsm) {
	SDL_Event mainEvent;

	if(SDL_PollEvent(&mainEvent)) {
		switch(mainEvent.type) {
		case SDL_QUIT:
			gsm->quit();
			break;

		case SDL_KEYDOWN:
			switch(mainEvent.key.keysym.sym) {
			case SDLK_SPACE:
				gsm->changeGameState(PlayState::Instance());
				break;
			case SDLK_ESCAPE:
				gsm->quit();
				break;
			}
			break;
		case SDL_MOUSEMOTION: 
			int x,y;
			SDL_GetMouseState(&x, &y);
			std::cout << "X:" << x << ", Y:" << y << std::endl;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (mainEvent.button.button == SDL_BUTTON_LEFT) {
				gsm->changeGameState(PlayState::Instance());
			}
			break;
		}
	}
}

void MenuState::update(GameStateManager *gsm, double dt) {
	//std::cout << "Pim rocks " << counter <<  std::endl;
}

void MenuState::draw(GameStateManager *gsm) {
	//Create surface and textures
	SDL_Surface* img = SDL_LoadBMP("menustate.bmp");
	SDL_Texture* texture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), img);



	Button* startButton = new Button(150,75,150,75,"start.bmp");
	Button* exitButton = new Button(150,165,150,75,"exit.bmp");

	//Add texture to renderer
	gsm->sdlInitializer->clearScreen();

	gsm->sdlInitializer->drawTexture(texture, NULL);
	startButton->render(gsm->sdlInitializer->getRenderer());
	exitButton->render(gsm->sdlInitializer->getRenderer());

	gsm->sdlInitializer->drawScreen();

	//Clean created textures/surfaces
	SDL_DestroyTexture(texture);  
	SDL_FreeSurface(img); 
}



MenuState::~MenuState(void)
{
}
