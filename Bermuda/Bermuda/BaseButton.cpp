#include "BaseButton.h"


BaseButton::BaseButton()
{
	active = false;
}

void BaseButton::align(int position, int total)
{
	PosY = ScreenHeight / 2 - (total + position * 2) * ConstHeight / 2;
	buttonRect.h = ConstHeight;
	buttonRect.w = ConstWidth;
	buttonRect.x = PosX;
	buttonRect.y = PosY;
}

void BaseButton::hover(int x, int y, GameStateManager *gsm)
{
	if (x >= buttonRect.x && x <= (buttonRect.x + buttonRect.w) &&
		y >= buttonRect.y && y <= (buttonRect.y + buttonRect.h))
	{
		if (active == false)
		{
			active = true;
			loadHoverPicture(gsm);
		}
	}
	else
	{
		if (active == true)
		{
			active = false;
			loadNormalPicture(gsm);
		}
	}
}

void BaseButton::clicked(int x, int y, GameStateManager *gsm)
{
	if (x >= buttonRect.x && x <= (buttonRect.x + buttonRect.w) &&
		y >= buttonRect.y && y <= (buttonRect.y + buttonRect.h))
	{
		action(gsm);
	}
}

void BaseButton::draw(GameStateManager *gsm)
{
	SDL_RenderCopy(gsm->sdlInitializer->getRenderer(), buttonImage, NULL, &buttonRect);
}

BaseButton::~BaseButton()
{
}
