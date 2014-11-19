#include "BasePauzeButton.h"

BasePauzeButton::BasePauzeButton()
{
	active = false;
}

void BasePauzeButton::placeAbove(BasePauzeButton* button)
{

	ButtonRect.x = ((int)ScreenWidth - ButtonRect.w) / 2;
	ButtonRect.y = button->ButtonRect.y - button->ButtonRect.h -15;
}

void BasePauzeButton::placeUnder(BasePauzeButton* button)
{
	ButtonRect.x = ((int)ScreenWidth - ButtonRect.w) / 2;
	ButtonRect.y = button->ButtonRect.y + button->ButtonRect.h +15;
}

int BasePauzeButton::getX()
{
	return ButtonRect.x;
}

int BasePauzeButton::getY()
{
	return ButtonRect.y;
}

int BasePauzeButton::getHeight()
{
	return ButtonRect.h;
}

int BasePauzeButton::getWidth()
{
	return ButtonRect.w;
}

void BasePauzeButton::createButton(std::string message)
{
	//making colors and opening font
	SDL_Color black = { 0, 0, 0 };
	SDL_Color white = { 255, 255, 255 };
	SDL_Color orange = { 235, 167, 8 };
	TTF_Font* staryDarzy = TTF_OpenFont((RESOURCEPATH + "fonts\\andyb.ttf").c_str(), 24);

	//Create menu button textures
	SDL_Surface* MessageSurface = TTF_RenderText_Blended(staryDarzy, message.c_str(), black);
	ButtonTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), MessageSurface);

	SDL_Surface* HoverMessageSurface = TTF_RenderText_Blended(staryDarzy, message.c_str(), orange);
	HoverButtonTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), HoverMessageSurface);

	ButtonRect.h = MessageSurface->h;
	ButtonRect.w = MessageSurface->w;

	ButtonRect.x = ((int)ScreenWidth - MessageSurface->w) / 2;
	ButtonRect.y = ((int)ScreenHeight - MessageSurface->h) / 2;

	SDL_FreeSurface(MessageSurface);
	SDL_FreeSurface(HoverMessageSurface);
	TTF_CloseFont(staryDarzy);
}

void BasePauzeButton::hover(int x, int y)
{
	if (x >= ButtonRect.x && x <= (ButtonRect.x + ButtonRect.w) &&
		y >= ButtonRect.y && y <= (ButtonRect.y + ButtonRect.h))
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

bool BasePauzeButton::clicked(int x, int y)
{
	if (x >= ButtonRect.x && x <= (ButtonRect.x + ButtonRect.w) &&
		y >= ButtonRect.y && y <= (ButtonRect.y + ButtonRect.h))
	{
		action();
		return true;
	}
	return false;
}

void BasePauzeButton::draw()
{
	SDL_Renderer* renderer = GameStateManager::Instance()->sdlInitializer->getRenderer();
	if (active == false)
	{
		SDL_RenderCopy(renderer, ButtonTexture, NULL, &ButtonRect);
	}
	else
	{
		SDL_RenderCopy(renderer, HoverButtonTexture, NULL, &ButtonRect);
	}
}

void BasePauzeButton::cleanup()
{
	SDL_DestroyTexture(ButtonTexture);
	SDL_DestroyTexture(HoverButtonTexture);
}

BasePauzeButton::~BasePauzeButton()
{
	cleanup();
}
