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
	align();
	playButton = new PlayButton(gsm);
	exitButton = new ExitButton(gsm);
	playButton->align(1, totalButtons);
	exitButton->align(0, totalButtons);
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


void MenuState::handleEvents(GameStateManager *gsm) {
	SDL_Event mainEvent;

	if (SDL_PollEvent(&mainEvent)) {
		int x, y;
		SDL_GetMouseState(&x, &y);
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
			playButton->hover(x, y, gsm);
			exitButton->hover(x, y, gsm);
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (mainEvent.button.button == SDL_BUTTON_LEFT) {
				playButton->clicked(x, y, gsm);
				exitButton->clicked(x, y, gsm);
			}
			break;
		}
	}
}

void MenuState::update(GameStateManager *gsm, double dt) {
	//std::cout << "Pim rocks " << counter <<  std::endl;
}

void MenuState::draw(GameStateManager *gsm) {
	gsm->sdlInitializer->clearScreen();
	SDL_RenderCopy(gsm->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);
	playButton->draw(gsm);
	exitButton->draw(gsm);
	gsm->sdlInitializer->drawScreen();

//	//Create surface and textures
//	SDL_Surface* img = SDL_LoadBMP("menustate.bmp");
//	SDL_Texture* texture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), img);
//
//
//
//	Button* startButton = new Button(150,75,150,75,"start.bmp");
//	Button* exitButton = new Button(150,165,150,75,"exit.bmp");
//
//	//Add texture to renderer
//	gsm->sdlInitializer->clearScreen();
//
//	gsm->sdlInitializer->drawTexture(texture, NULL);
//	startButton->render(gsm->sdlInitializer->getRenderer());
//	exitButton->render(gsm->sdlInitializer->getRenderer());
//
//	gsm->sdlInitializer->drawScreen();
//
//	//Clean created textures/surfaces
//	SDL_DestroyTexture(texture);  
//	SDL_FreeSurface(img); 
}



MenuState::~MenuState(void)
{
	SDL_DestroyTexture(backgroundTexture);
	delete playButton;
	delete exitButton;
}
