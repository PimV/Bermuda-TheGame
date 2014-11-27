#include "PauzeResumeButton.h"
#include "PauseState.h"


PauzeResumeButton::PauzeResumeButton()
{
	init();
}

void PauzeResumeButton::init()
{
	std::string Message = "Resume";
	createButton(Message, 24, 1);
}

void PauzeResumeButton::action()
{
	GameStateManager::Instance()->popState();
}

PauzeResumeButton::~PauzeResumeButton()
{
}
