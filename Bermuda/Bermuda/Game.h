#pragma once
#include <iostream>
#include <thread>

class Game
{
private:
	std::thread gameLoopThread;
public:
	Game(void);
	~Game(void);
	static void gameLoop();
};

