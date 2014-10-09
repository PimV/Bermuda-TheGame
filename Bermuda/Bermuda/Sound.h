#pragma once
#include <SDL_mixer.h>

class Sound
{
public:
	Sound();
	virtual ~Sound();

	Mix_Music* gMusic[5];
	Mix_Chunk* gChunk[10];
	bool* quit;

	bool init();
	void playMenuMusic();
	void playGameMusic();

};

