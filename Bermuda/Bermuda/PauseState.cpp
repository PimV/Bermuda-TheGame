#include "PauseState.h"
#include <iostream>


PauseState::PauseState()
{
}

void PauseState::init(GameStateManager* gsm)
{
	this->gsm = gsm;
}

void PauseState::cleanup()
{
}

void PauseState::pause()
{
}

void PauseState::resume()
{
}

void PauseState::handleEvents(GameStateManager* gsm)
{
	SDL_Event mainEvent;

	if(SDL_PollEvent(&mainEvent)) 
	{
		switch(mainEvent.type) 
		{
		case SDL_KEYDOWN:
			switch(mainEvent.key.keysym.sym) 
			{
			case SDLK_ESCAPE:
				this->removeState();
				break;
			}
			break;
		}
	}
}

void PauseState::update(GameStateManager* gsm, double dt)
{
	std::cout << "Active: pause state" << std::endl;
}

void PauseState::draw(GameStateManager* gsm)
{
	//TODO: MEMORY LEAK omdat ik nog niet CLEAR sdl window aanroep omdat dat het beeld van playstate word weggehaald
	/*
		IS DIT EEN LEAK?
	*/
	
	SDL_Texture* texture = IMG_LoadTexture(this->gsm->sdlInitializer->getRenderer(), "pausemenu.png");
	if(texture == NULL)
	{
		std::cout << "aap" << std::endl;
	}
	SDL_Rect rect;
	rect.w = 200;
	rect.h = 400;
	rect.x = 200;
	rect.y = 200;
	this->gsm->sdlInitializer->drawTexture(texture, &rect);
	
	SDL_DestroyTexture(texture);  

	
	gsm->sdlInitializer->drawScreen();
}

void PauseState::removeState()
{
	this->gsm->popState();
}

PauseState::~PauseState()
{
}
