#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <chrono>

Game::Game(void)
{
	//Start Gameloop
	Game::gameLoop();
}


Game::~Game(void)
{
}

/*
*
*
*/

void Game::gameLoop() {
	double TARGET_FPS = 60;
	double OPTIMAL_TIME = 1000 / TARGET_FPS;

	LARGE_INTEGER frequency;        // ticks per second
	LARGE_INTEGER previousTime, currentTime, afterLoopTime;           // ticks
	QueryPerformanceFrequency(&frequency);
	QueryPerformanceCounter(&previousTime);

	double lastLoopTime = previousTime.QuadPart * 1000.0 / frequency.QuadPart;

	long lastFpsTime = 0;
	int fps = 0;

	while (true) {		
		//Take current Time
		QueryPerformanceCounter(&currentTime);
		//Take current time - previous time
		long updateLength = (currentTime.QuadPart - previousTime.QuadPart) * 1000.0 / frequency.QuadPart;

		//Previous time = current time
		previousTime = currentTime;
		//Calculate delta
		double delta = updateLength / OPTIMAL_TIME;

		//Add time difference to lastFpsTime
		lastFpsTime += updateLength;
		//Increase FPS since one frame has passed
		fps++;

		//If lastFpsTime > 1000 ms, set FPS to 0 and start re-calculating
		if (lastFpsTime >= 1000) {
			//std::cout << fps << " " << clock() << std::endl;
			lastFpsTime = 0;
			fps = 0;
		}

		//UPDATE SHIT


		//Get time after loop
		QueryPerformanceCounter(&afterLoopTime);
		//Sleep if needed (if time took longer than optimal)
		if ((((previousTime.QuadPart - afterLoopTime.QuadPart) * 1000.0 / frequency.QuadPart) + OPTIMAL_TIME) > 0) {
			Sleep((((previousTime.QuadPart - afterLoopTime.QuadPart) * 1000.0 / frequency.QuadPart) + OPTIMAL_TIME));
		}
	}
}
