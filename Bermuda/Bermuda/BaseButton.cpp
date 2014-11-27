#include "BaseButton.h"


BaseButton::BaseButton()
{
	reset();
}

void BaseButton::reset()
{
	active = false;
}

void BaseButton::placeLeftAboveButton(BaseButton* button)
{

	buttonRect.x = button->buttonRect.x;
	buttonRect.y = button->buttonRect.y - button->buttonRect.h - 15;
}

void BaseButton::placeLeftUnderButton(BaseButton* button)
{
	buttonRect.x = button->buttonRect.x;
	buttonRect.y = button->buttonRect.y + button->buttonRect.h + 15;
}

void BaseButton::placeMidScreenAbove(BaseButton* button)
{

	buttonRect.x = ((int)ScreenWidth - buttonRect.w) / 2;
	buttonRect.y = button->buttonRect.y - button->buttonRect.h - 15;
}

void BaseButton::placeMidScreenUnder(BaseButton* button)
{
	buttonRect.x = ((int)ScreenWidth - buttonRect.w) / 2;
	buttonRect.y = button->buttonRect.y + button->buttonRect.h + 15;
}

void BaseButton::placeMidUnder(int x, int y)
{
	buttonRect.x = x - buttonRect.h / 2;
	buttonRect.y = y;
}

int BaseButton::getX()
{
	return buttonRect.x;
}

int BaseButton::getY()
{
	return buttonRect.y;
}

int BaseButton::getHeight()
{
	return buttonRect.h;
}

int BaseButton::getWidth()
{
	return buttonRect.w;
}

void BaseButton::createButton(std::string message, int fontSize, int initialColor)
{
	//making colors and opening font
	SDL_Color color;
	if (initialColor == 0)
	{
		color.r = 255; color.g = 255; color.b = 255;
	}
	else if (initialColor == 1)
	{
		color.r = 0; color.g = 0; color.b = 0;
	}
	SDL_Color orange = { 235, 167, 8 };
	TTF_Font* staryDarzy = TTF_OpenFont((RESOURCEPATH + "fonts\\segoeuib.ttf").c_str(), fontSize);

	//Create menu button textures
	SDL_Surface* MessageSurface = TTF_RenderText_Blended(staryDarzy, message.c_str(), color);
	buttonTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), MessageSurface);

	SDL_Surface* HoverMessageSurface = TTF_RenderText_Blended(staryDarzy, message.c_str(), orange);
	buttonHoverTexture = SDL_CreateTextureFromSurface(GameStateManager::Instance()->sdlInitializer->getRenderer(), HoverMessageSurface);

	buttonRect.h = MessageSurface->h;
	buttonRect.w = MessageSurface->w;

	SDL_FreeSurface(MessageSurface);
	SDL_FreeSurface(HoverMessageSurface);
	TTF_CloseFont(staryDarzy);
}

void BaseButton::placeMid()
{
	buttonRect.x = ((int)ScreenWidth - buttonRect.w) / 2;
	buttonRect.y = ((int)ScreenHeight - buttonRect.h) / 2;
}

void BaseButton::placeLeftMid()
{
	buttonRect.x = 50;
	buttonRect.y = ((int)ScreenHeight - buttonRect.h) / 2;
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
	SDL_Renderer* renderer = GameStateManager::Instance()->sdlInitializer->getRenderer();
	if (active == false)
	{
		SDL_RenderCopy(renderer, buttonTexture, NULL, &buttonRect);
	}
	else
	{
		SDL_RenderCopy(renderer, buttonHoverTexture, NULL, &buttonRect);
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
