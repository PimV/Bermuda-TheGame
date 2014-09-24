#include "header_loader.h"
#include "Game.h"

#include <iostream>
#include <thread>
#include <future>


int main(int argc, char* args[])
{
	Game* game = new Game();
	Game::runGameThread();
	std::cin.get();
	return 0;
}