#pragma once
#include <SDL.h>

class InteractiveBase
{
public:
	InteractiveBase(void);
	virtual ~InteractiveBase(void);

	virtual void setRangeValue(int value) = 0;
	virtual int getRangeValue() = 0;
	virtual void setLocationRect(SDL_Rect rect) = 0;
	virtual SDL_Rect getLocationRect() = 0;

private:
	int rangeValue;
	SDL_Rect interactiveLocationRect;
	SDL_Rect interactiveRangeRect;

	virtual void createRangeRect() = 0;
};

