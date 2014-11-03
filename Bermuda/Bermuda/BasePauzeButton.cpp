#include "BasePauzeButton.h"

BasePauzeButton::BasePauzeButton()
{
	active = false;
}

void BasePauzeButton::placeAbove(BasePauzeButton* button)
{
	ButtonRect.h = button->ButtonRect.h;
	ButtonRect.w = button->ButtonRect.w;
	ButtonRect.x = button->ButtonRect.x;
	ButtonRect.y = button->ButtonRect.y - button->ButtonRect.h * 2;
}

void BasePauzeButton::placeUnder(BasePauzeButton* button)
{
	ButtonRect.h = button->ButtonRect.h;
	ButtonRect.w = button->ButtonRect.w;
	ButtonRect.x = button->ButtonRect.x;
	ButtonRect.y = button->ButtonRect.y + button->ButtonRect.h * 2;
}

void BasePauzeButton::hover(int x, int y, GameStateManager *gsm)
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

void BasePauzeButton::clicked(int x, int y, GameStateManager *gsm)
{
	if (x >= ButtonRect.x && x <= (ButtonRect.x + ButtonRect.w) &&
		y >= ButtonRect.y && y <= (ButtonRect.y + ButtonRect.h))
	{
		action(gsm);
	}
}
void BasePauzeButton::draw(GameStateManager* gsm)
{
	if (active == false)
	{
		SDL_RenderCopy(gsm->sdlInitializer->getRenderer(), ButtonTexture, NULL, &ButtonRect);
	}
	else
	{
		SDL_RenderCopy(gsm->sdlInitializer->getRenderer(), HoverButtonTexture, NULL, &ButtonRect);
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
