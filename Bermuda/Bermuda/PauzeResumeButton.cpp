#include "PauzeResumeButton.h"
#include "PauseState.h"


PauzeResumeButton::PauzeResumeButton(GameStateManager* gsm)
{
	init(gsm);
}

void PauzeResumeButton::init(GameStateManager* gsm)
{
	//making colors and opening font
	SDL_Color white = { 255, 255, 255 };
	SDL_Color orange = { 235, 167, 8 };
	TTF_Font* staryDarzy = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 16);

	//create resume button textures
	std::string Message = "Resume";
	SDL_Surface* MessageSurface = TTF_RenderText_Blended(staryDarzy, Message.c_str(), white);
	ButtonTexture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), MessageSurface);

	SDL_Surface* HoverMessageSurface = TTF_RenderText_Blended(staryDarzy, Message.c_str(), orange);
	HoverButtonTexture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), HoverMessageSurface);

	SDL_FreeSurface(MessageSurface);
	SDL_FreeSurface(HoverMessageSurface);
	TTF_CloseFont(staryDarzy);
}

void PauzeResumeButton::action(GameStateManager* gsm)
{
	gsm->popState();
}

PauzeResumeButton::~PauzeResumeButton()
{
}
