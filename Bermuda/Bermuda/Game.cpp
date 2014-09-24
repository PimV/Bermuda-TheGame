#include "Game.h"
#include <Windows.h>
#include <iostream>
#include <chrono>
#include <thread>

Game::Game(void)
{
	//Start Gameloop

}


Game::~Game(void)
{

}

void Game::runGameThread() {
	std::thread gameLoopThread(&Game::gameLoop);
	gameLoopThread.detach();
}

/*
*
*
*/

void Game::gameLoop() {
	double TARGET_FPS = 60;
	double OPTIMAL_TIME = 1000 / TARGET_FPS;

	//Instantiate Large Integers
	LARGE_INTEGER frequency; // ticks per second
	LARGE_INTEGER previousTime, currentTime, afterLoopTime; // ticks
	//Set Frequency
	QueryPerformanceFrequency(&frequency);
	//Set Previous Time (for the first time)
	QueryPerformanceCounter(&previousTime);

	//Instantiate FPS variables and set to 0
	long lastFpsTime = 0;
	int fps = 0;

	while (true) {		
		//Take current Time
		QueryPerformanceCounter(&currentTime);
		//Calculate difference (previousTime - currentTime)
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
			std::cout << fps << std::endl;
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
