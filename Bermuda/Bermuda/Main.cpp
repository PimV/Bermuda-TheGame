#include "header_loader.h"
#include "Game.h"

#include <iostream>
#include <thread>
#include <future>
#include "Windows.h"


int main(int argc, char* args[])
{
	//Game* game = new Game();
	Game game;
	Sleep(2000);
	delete &game;
	//	Game::runGameThread();
	std::cin.get();
	return 0;
}