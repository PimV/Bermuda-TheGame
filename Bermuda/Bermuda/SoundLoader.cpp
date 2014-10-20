#include "SoundLoader.h"
#include "header_loader.h"

#include <SDL_thread.h>
#include <time.h>
#include <iostream>
#include <thread>

SoundLoader::SoundLoader()
{
	if (!init())
	{
		printf("Failed to initialize SoundLoader!\n");
	}
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
		success = false;
	}
	else
	{
		//if (!loadMenuMusic())
		//{
		//	printf("Failed to load menu music\n");
		//	success = false;
		//}

		//if (!loadGameMusic())
		//{
		//	printf("Failed to load game music\n");
		//	success = false;
		//}
	}

	return success;
}

void SoundLoader::playGameMusic()
{
	//std::thread t1(threadGameMusic);

	SDL_Thread* gameMusicThread = SDL_CreateThread(this->threadGameMusic, "GameMusicThread", &gameMusic);
	if (gameMusicThread == NULL) {
		printf("\nSDL_CreateThread failed: %s\n", SDL_GetError());
	}
}

int SoundLoader::threadGameMusic(void* data)
{
	//// convert data to vector
	////std::vector<Mix_Music*> gameMusic;
	////gameMusic = reinterpret_cast<std::vector<Mix_Music*>>(data);


	Mix_HaltMusic(); // Stop any music that's already playing

	bool running = true;

	// Thread
	while (running)
	{
		//std::cout << "Music running" << std::endl;

		if (Mix_PlayingMusic() == 0) {
			std::cout << "Music start" << std::endl;

			srand(time(NULL));

			//int i = rand() % gameMusic.size();
			//Mix_PlayMusic(gameMusic[i], 0);

			int i = rand() % 5;
			if (i == 0) {
				Mix_PlayMusic(Mix_LoadMUS((RESOURCEPATH + "music/game/Carefree.mp3").c_str()), 0);
			}
			else if (i == 1) {
				Mix_PlayMusic(Mix_LoadMUS((RESOURCEPATH + "music/game/Run Amok.mp3").c_str()), 0);
			}
			else if (i == 2) {
				Mix_PlayMusic(Mix_LoadMUS((RESOURCEPATH + "music/game/Rites.mp3").c_str()), 0);
			}
			else if (i == 3) {
				Mix_PlayMusic(Mix_LoadMUS((RESOURCEPATH + "music/game/Pamgaea.mp3").c_str()), 0);
			}
			else if (i == 4) {
				Mix_PlayMusic(Mix_LoadMUS((RESOURCEPATH + "music/game/Reign Supreme.mp3").c_str()), 0);
			}
		} 
		
	//	//std::chrono::milliseconds dura(50);
	//	//std::this_thread::sleep_for(dura);
		SDL_Delay(50);
	}

	return 0;
}

//bool SoundLoader::loadMenuMusic()
//{
//	bool success = true;
//
//	menuMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/menu/Rollin at 5.mp3").c_str()));
//	menuMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/menu/Rollin at 5 - electronic.mp3").c_str()));
//	for (size_t i = 0; i < menuMusic.size(); i++)
//	{
//		if (menuMusic[i] == NULL)
//		{
//			printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
//			success = false;
//		}
//	}
//
//	return success;
//}

//bool SoundLoader::loadGameMusic()
//{
//	bool success = true;
//
//	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Rites.mp3").c_str()));
//	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Run Amok.mp3").c_str()));
//	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Carefree.mp3").c_str()));
//	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Lightless Dawn.mp3").c_str()));
//	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Pamgaea.mp3").c_str()));
//	gameMusic.push_back(Mix_LoadMUS((RESOURCEPATH + "music/game/Reign Supreme.mp3").c_str()));
//	for (size_t i = 0; i < gameMusic.size(); i++)
//	{
//		if (gameMusic[i] == NULL)
//		{
//			printf("Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError());
//			success = false;
//		}
//	}
//
//	return success;
//}

void SoundLoader::playMenuMusic()
{
	//srand(time(NULL));

	//int i = rand() % menuMusic.size();
	//Mix_PlayMusic(menuMusic[i], -1);
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
