#include "header_loader.h"
#include "Game.h"
#include "Player.h"

#include <iostream>
#include <thread>
#include <future>
#include <Windows.h>

#include "Rabbit.h"
#include "Spawnpoint.h"

int main(int argc, char* args[])
{
	Rabbit* rabbit = new Rabbit(1, 1, 1, 20, 1, new Spawnpoint(2));
	rabbit->walk();

	//Player *p1 = new Player(2);
	//Player *p2 = new Player(88);
	//std::cout << p1->moveSpeed << " " << p2->moveSpeed;
	Game game;

	std::cin.get();
	return 0;
}