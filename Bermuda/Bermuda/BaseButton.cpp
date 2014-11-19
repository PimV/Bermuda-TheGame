#include "BaseButton.h"


BaseButton::BaseButton()
{
	active = false;
}

void BaseButton::placeAbove(BaseButton* button)
{

	buttonRect.x = button->buttonRect.x;
	buttonRect.y = button->buttonRect.y - button->buttonRect.h - 15;
}

void BaseButton::placeUnder(BaseButton* button)
{
	buttonRect.x = button->buttonRect.x;
	buttonRect.y = button->buttonRect.y + button->buttonRect.h + 15;
}

void BaseButton::createButton(std::string message)
{
	//making colors and opening font
	SDL_Color white = { 255, 255, 255 };
	SDL_Color orange = { 235, 167, 8 };
	TTF_Font* staryDarzy = TTF_OpenFont((RESOURCEPATH + "fonts\\segoeuib.ttf").c_str(), 60);

	//Create menu button textures
	SDL_Surface* MessageSurface = TTF_RenderText_Blended(staryDarzy, message.c_str(), white);
	buttonTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), MessageSurface);

	SDL_Surface* HoverMessageSurface = TTF_RenderText_Blended(staryDarzy, message.c_str(), orange);
	buttonHoverTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), HoverMessageSurface);

	buttonRect.h = MessageSurface->h;
	buttonRect.w = MessageSurface->w;

	buttonRect.x = 50;
	buttonRect.y = ((int)ScreenHeight - MessageSurface->h) / 2;

	SDL_FreeSurface(MessageSurface);
	SDL_FreeSurface(HoverMessageSurface);
	TTF_CloseFont(staryDarzy);
}

void BaseButton::hover(int x, int y)
{
	if (x >= buttonRect.x && x <= (buttonRect.x + buttonRect.w) &&
		y >= buttonRect.y && y <= (buttonRect.y + buttonRect.h))
	{
		if (active == false)
		{
			active = true;
		}
	}
	else
	{
		if (active == true)
		{
			active = false;
		}
	}
}

bool BaseButton::clicked(int x, int y)
{
	if (x >= buttonRect.x && x <= (buttonRect.x + buttonRect.w) &&
		y >= buttonRect.y && y <= (buttonRect.y + buttonRect.h))
	{
		action();
		return true;
	}
	return false;
}

void BaseButton::draw()
{
	if (active == false)
	{
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), buttonTexture, NULL, &buttonRect);
	}
	else
	{
		SDL_RenderCopy(GameStateManager::Instance()->sdlInitializer->getRenderer(), buttonHoverTexture, NULL, &buttonRect);
	}
}

void BaseButton::cleanup()
{
	SDL_DestroyTexture(buttonTexture);
	SDL_DestroyTexture(buttonHoverTexture);
}

BaseButton::~BaseButton()
{
	cleanup();
}
