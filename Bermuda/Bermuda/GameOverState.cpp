#include "GameOverState.h"
#include <iostream>
#include <SDL_ttf.h>
#include "MenuState.h"

GameOverState GameOverState::m_GameOverState;

GameOverState::GameOverState()
{
}

void GameOverState::init(GameStateManager* gsm) {
	this->gsm = gsm;

	backgroundTexture = IMG_LoadTexture(gsm->sdlInitializer->getRenderer(), (RESOURCEPATH + "Textures/gameover_Background.png").c_str());
	if (backgroundTexture == NULL)
	{
		std::cout << "Error loading startmenu background" << std::endl << "Error 2" << std::endl;
		system("pause");
	}
	backgroundRect.x = 0;
	backgroundRect.y = 0;
	backgroundRect.w = ScreenWidth;
	backgroundRect.h = ScreenHeight;

	TTF_Font* staryDarzyLarge = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 32);
	SDL_Color white = { 255, 255, 255 };
	std::string gameOverMessage = "You died. You survived " + to_string(GameTimer::Instance()->getDaysSurvived()) + " days";
	SDL_Surface* gameOverMessageSurface = TTF_RenderText_Blended(staryDarzyLarge, gameOverMessage.c_str(), white);

	TTF_Font* staryDarzySmall = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 16);
	std::string continueMessage = "Press enter to return to menu";
	SDL_Surface* continueMessageSurface = TTF_RenderText_Blended(staryDarzySmall, continueMessage.c_str(), white);

	gameOverMessageTexture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), gameOverMessageSurface);
	continueMessageTexture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), continueMessageSurface);

	gameoverMessageRect.x = ((int)ScreenWidth - gameOverMessageSurface->w) / 2;
	gameoverMessageRect.y = ((int)ScreenHeight - gameOverMessageSurface->h) / 2;
	gameoverMessageRect.h = gameOverMessageSurface->h;
	gameoverMessageRect.w = gameOverMessageSurface->w;

	continueMessageRect.x = ((int)ScreenWidth - continueMessageSurface->w) / 2;
	continueMessageRect.y = gameoverMessageRect.y + gameOverMessageSurface->h;
	continueMessageRect.h = continueMessageSurface->h;
	continueMessageRect.w = continueMessageSurface->w;

	SDL_FreeSurface(gameOverMessageSurface);
	TTF_CloseFont(staryDarzyLarge);
}

void GameOverState::cleanup()
{
	SDL_DestroyTexture(backgroundTexture);
	SDL_DestroyTexture(gameOverMessageTexture);
	SDL_DestroyTexture(continueMessageTexture);
}

void GameOverState::pause()
{
}

void GameOverState::resume()
{
}

void GameOverState::handleEvents(SDL_Event mainEvent){
	switch (mainEvent.type)
	{
	case SDL_KEYDOWN:
		switch (mainEvent.key.keysym.sym){
		case SDLK_RETURN:
			this->gsm->changeGameState(MenuState::Instance());
			break;
		}
	}
}

void GameOverState::update(double dt){

}

void GameOverState::draw(){
	SDL_RenderCopy(gsm->sdlInitializer->getRenderer(), backgroundTexture, NULL, &backgroundRect);
	SDL_RenderCopy(gsm->sdlInitializer->getRenderer(), gameOverMessageTexture, NULL, &gameoverMessageRect);
	SDL_RenderCopy(gsm->sdlInitializer->getRenderer(), continueMessageTexture, NULL, &continueMessageRect);
}

GameOverState::~GameOverState()
{
	cleanup();
}
