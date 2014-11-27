#include "PlayButton.h"


PlayButton::PlayButton()
{
	init();
}

void PlayButton::init()
{
	std::string Message = "Play";
	createButton(Message);
}

void PlayButton::action()
{
	GameStateManager::Instance()->changeGameState(PlayState::Instance());
}

PlayButton::~PlayButton()
{
}
