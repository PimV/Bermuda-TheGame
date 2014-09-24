#include "StartHere.h"
#include <iostream>

#include <SDL.h>
#include <SDL_image.h>

StartHere::StartHere(void)
{
}


StartHere::~StartHere(void)
{
}

/**
BEFORE STARTING, BE SURE NOT TO FORGET TO SET YOUR OWN INCLUDE/LIBRARY DIRECTORIES

(Project -> Properties -> VC++ Directories -> Set your directories)

AND BE SURE TO COPY THE "SDL2.DLL" FILE INTO YOUR PROJECTS ROOT FOLDER (From the 32-bit binary (X86))

IF ALL IS CORRECT, YOUR PROJECT SHOULD HAVE INCLUDED SDL BY NOW
**/
int main(int argc, char* args[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	std::cin.get();

	SDL_Quit();

	return 0;
}