#include "PauzeAchievementsButton.h"
#include "PauseState.h"


PauzeAchievementsButton::PauzeAchievementsButton(GameStateManager* gsm)
{
	init(gsm);
}

void PauzeAchievementsButton::init(GameStateManager* gsm)
{
	//making colors and opening font
	SDL_Color white = { 255, 255, 255 };
	SDL_Color orange = { 235, 167, 8 };
	TTF_Font* staryDarzy = TTF_OpenFont((RESOURCEPATH + "fonts\\Starzy_Darzy.ttf").c_str(), 16);

	//Create menu button textures
	std::string Message = "Achievements";
	SDL_Surface* MessageSurface = TTF_RenderText_Blended(staryDarzy, Message.c_str(), white);
	ButtonTexture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), MessageSurface);

	SDL_Surface* HoverMessageSurface = TTF_RenderText_Blended(staryDarzy, Message.c_str(), orange);
	HoverButtonTexture = SDL_CreateTextureFromSurface(gsm->sdlInitializer->getRenderer(), HoverMessageSurface);

	ButtonRect.h = MessageSurface->h;
	ButtonRect.w = MessageSurface->w;

	SDL_FreeSurface(MessageSurface);
	SDL_FreeSurface(HoverMessageSurface);
	TTF_CloseFont(staryDarzy);
}

void PauzeAchievementsButton::action(GameStateManager* gsm)
{
	PauseState::Instance()->setCurWindow(1);
}

PauzeAchievementsButton::~PauzeAchievementsButton()
{
}
