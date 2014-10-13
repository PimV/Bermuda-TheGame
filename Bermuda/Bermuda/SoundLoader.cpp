#include "SoundLoader.h"
#include <SDL.h>
#include <SDL_thread.h>
#include <iostream>

SoundLoader::SoundLoader()
{
	init();
}

bool SoundLoader::init()
{
	bool success = true;

	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}

	//menuMusic.push_back(Mix_LoadMUS("music/menu/music1.mp3"));
	//menuMusic.push_back(Mix_LoadMUS("music/menu/music2.mp3"));
	//for (size_t i = 0; i < menuMusic.size(); i++)
	//{
	//	if (menuMusic[i] == NULL)
	//	{
	//		printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
	//		success = false;
	//	}
	//}

	//gameMusic.push_back(Mix_LoadMUS("music/games/Rites.mp3"));
	//gameMusic.push_back(Mix_LoadMUS("music/game/music2.mp3"));
	//gameMusic.push_back(Mix_LoadMUS("music/game/music3.mp3"));
	//gameMusic.push_back(Mix_LoadMUS("music/game/music4.mp3"));
	//gameMusic.push_back(Mix_LoadMUS("music/game/music5.mp3"));
	//gameMusic.push_back(Mix_LoadMUS("music/game/music6.mp3"));
	//gameMusic.push_back(Mix_LoadMUS("music/game/music7.mp3"));
	//gameMusic.push_back(Mix_LoadMUS("music/game/music8.mp3"));
	//gameMusic.push_back(Mix_LoadMUS("music/game/music9.mp3"));
	//gameMusic.push_back(Mix_LoadMUS("music/game/music10.mp3"));
	//for (size_t i = 0; i < gameMusic.size(); i++)
	//{
	//	if (gameMusic[i] == NULL)
	//	{
	//		printf("Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError());
	//		success = false;
	//	}
	//}


	return success;
}

void SoundLoader::playGameMusic()
{
	std::cout << "Playing game music..";

	Mix_Music* testMusic = Mix_LoadMUS("Rites.mp3");
	if (testMusic == NULL) {
		std::cout << "Can't load music";
	}
	Mix_PlayMusic(testMusic, -1);
}

void SoundLoader::playMenuMusic()
{

}

SoundLoader::~SoundLoader()
{
	for (size_t i = 0; i < menuMusic.size(); i++)
	{
		Mix_FreeMusic(menuMusic[i]);
		menuMusic[i] = NULL;
	}

	for (size_t i = 0; i < gameMusic.size(); i++)
	{
		Mix_FreeMusic(gameMusic[i]);
		gameMusic[i] = NULL;
	}
}
