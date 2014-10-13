#include <SDL.h>
#include <SDL_thread.h>
#include "SoundLoader.h"
#include "header_loader.h"
#include <time.h>
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

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
	}
	else 
	{
		menuMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/menu/Rollin at 5.mp3").c_str()));
		menuMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/menu/Rollin at 5 - electronic.mp3").c_str()));
		for (size_t i = 0; i < menuMusic.size(); i++)
		{
			if (menuMusic[i] == NULL)
			{
				printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
				success = false;
			}
		}

		gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Rites.mp3").c_str()));
		gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Run Amok.mp3").c_str()));
		gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Carefree.mp3").c_str()));
		gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Lightless Dawn.mp3").c_str()));
		gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Pamgaea.mp3").c_str()));
		gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Reign Supreme.mp3").c_str()));
		for (size_t i = 0; i < gameMusic.size(); i++)
		{
			if (gameMusic[i] == NULL)
			{
				printf("Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError());
				success = false;
			}
		}
	}

	return success;
}

void SoundLoader::playGameMusic()
{
	srand(time(NULL));

	

	int i = rand() % gameMusic.size();
	Mix_PlayMusic(gameMusic[i], -1);
}

void SoundLoader::playMenuMusic()
{
	srand(time(NULL));

	int i = rand() % menuMusic.size();
	Mix_PlayMusic(menuMusic[i], -1);
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
