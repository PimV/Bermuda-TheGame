#include "ExitButton.h"


ExitButton::ExitButton(GameStateManager *gsm) : BaseButton()
{
	init();
	loadNormalPicture(gsm);
}

void ExitButton::init()
{
	normalPicture = RESOURCEPATH + "Textures/exit.png";
	hoverPicure = RESOURCEPATH + "Textures/exit_hover.png";
}

void ExitButton::action(GameStateManager *gsm)
{
	exit(0);
}

void ExitButton::loadNormalPicture(GameStateManager *gsm)
{
	SDL_DestroyTexture(buttonImage);
	buttonImage = IMG_LoadTexture(gsm->sdlInitializer->getRenderer(), normalPicture.c_str());
}

void ExitButton::loadHoverPicture(GameStateManager *gsm)
{
	SDL_DestroyTexture(buttonImage);
	buttonImage = IMG_LoadTexture(gsm->sdlInitializer->getRenderer(), hoverPicure.c_str());
}

ExitButton::~ExitButton()
{
}
