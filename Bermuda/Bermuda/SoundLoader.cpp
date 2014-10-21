#include "SoundLoader.h"
#include "header_loader.h"
#include "StateType.h"

#include <SDL_thread.h>
#include <time.h>
#include <iostream>
#include <thread>

#pragma region Constructor & Destructor
SoundLoader::SoundLoader()
{
	target_time_ms = 180000; // 3 minutes
		
	if (!initialiseSound())
	{
		printf("Failed to initialize SoundLoader!\n");
	}

	initialiseThread();
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

#pragma endregion

#pragma region Public Methods
void SoundLoader::playGameMusic()
{
	stateType = StateType::Game;
	haltMusic = true;
}

void SoundLoader::playMenuMusic()
{
	stateType = StateType::Menu;
	haltMusic = true;
}

void SoundLoader::closeMusic()
{
	quit = true;
}

SoundLoader SoundLoader::m_SoundLoader;

#pragma endregion

#pragma region Private Methodes
void SoundLoader::initialiseThread()
{
	std::thread t(&SoundLoader::threadMusic, this);
	t.detach();
}


bool SoundLoader::initialiseSound()
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
		success = false;
	}
	else
	{
		if (!loadMenuMusic())
		{
			printf("Failed to load menu music\n");
			success = false;
		}

		if (!loadGameMusic())
		{
			printf("Failed to load game music\n");
			success = false;
		}
	}

	return success;
}

void SoundLoader::threadMusic()
{
	quit = false;
	//long currentTime = SDL_GetTicks();
	//long prevTime = 0;
	
	// Stop any music that's already playing
	Mix_FadeOutMusic(1500); 

	while (!quit)
	{
		if (Mix_PlayingMusic() == 0) {

			srand(time(NULL));
			int trackNr;

			switch (stateType)
			{
			case StateType::Setup:
				break;
			case StateType::Game:
				trackNr = rand() % gameMusic.size();
				Mix_FadeInMusic(gameMusic[trackNr], 0, 1500);
				break;
			case StateType::Menu:
				trackNr = rand() % menuMusic.size();
				Mix_FadeInMusic(menuMusic[trackNr], 0, 1500);
				break;
			case StateType::Pause:
				break;
			default:
				break;
			}
		}

		if (haltMusic == true) 
		{
			Mix_FadeOutMusic(1500);
			haltMusic = false;
		}

		/*currentTime = SDL_GetTicks();
		if (currentTime - prevTime > target_time_ms)
		{
			std::cout << currentTime - prevTime << std::endl;
			prevTime = currentTime;
			Mix_FadeOutMusic(1500);
		}*/

		std::chrono::milliseconds dura(50);
		std::this_thread::sleep_for(dura);
	}
	quit = true;
	Mix_FadeOutMusic(1500);
}

bool SoundLoader::loadMenuMusic()
{
	bool success = true;

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

	return success;
}

bool SoundLoader::loadGameMusic()
{
	bool success = true;

	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Bahara.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Behemos.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Colosseoum Main.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Creep.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Crisis.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Darkon.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Enrlun.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Flaris.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/General.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Kailun.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Maskball.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Mystery.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Playground.mp3").c_str()));
	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Saint Morning.mp3").c_str()));
	for (size_t i = 0; i < gameMusic.size(); i++)
	{
		if (gameMusic[i] == NULL)
		{
			printf("Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError());
			success = false;
		}
	}

	return success;
}
#pragma endregion
