#include "ExitButton.h"


ExitButton::ExitButton(GameStateManager *gsm) : BaseButton()
{
	init();
	loadNormalPicture(gsm);
}

void ExitButton::init()
{
	normalPicture = "Textures/exit.png";
	hoverPicure = "Textures/exit_hover.png";
}

void ExitButton::action(GameStateManager *gsm)
{
	std::cout << "exit clicked" << std::endl;
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
