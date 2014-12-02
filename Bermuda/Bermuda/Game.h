#pragma once
#include "GameStateManager.h"
#include <iostream>
#include <thread>


class Game
{
private:
	GameStateManager* gsm;
	std::thread gameLoopThread;
public:
	Game(void);
	static void gameLoop(GameStateManager* gsm);
	virtual ~Game(void);

};

