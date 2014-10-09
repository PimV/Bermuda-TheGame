#include "PlayButton.h"


PlayButton::PlayButton(GameStateManager *gsm) : BaseButton()
{
	init();
	loadNormalPicture(gsm);
}

void PlayButton::init()
{
	normalPicture = "Textures/play.png";
	hoverPicure = "Textures/play_hover.png";
}

void PlayButton::action(GameStateManager *gsm)
{
	gsm->changeGameState(PlayState::Instance());
}

void PlayButton::loadNormalPicture(GameStateManager *gsm)
{
	SDL_DestroyTexture(buttonImage);
	buttonImage = IMG_LoadTexture(gsm->sdlInitializer->getRenderer(), normalPicture.c_str());
}

void PlayButton::loadHoverPicture(GameStateManager *gsm)
{
	SDL_DestroyTexture(buttonImage);
	buttonImage = IMG_LoadTexture(gsm->sdlInitializer->getRenderer(), hoverPicure.c_str());
}

PlayButton::~PlayButton()
{
}
