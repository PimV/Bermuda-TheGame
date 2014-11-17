#include "PauzeResumeButton.h"
#include "PauseState.h"


PauzeResumeButton::PauzeResumeButton(GameStateManager* gsm)
{
	init(gsm);
}

void PauzeResumeButton::init(GameStateManager* gsm)
{
	std::string Message = "Resume";
	createButton(Message);
}

void PauzeResumeButton::action(GameStateManager* gsm)
{
	gsm->popState();
}

PauzeResumeButton::~PauzeResumeButton()
{
}
