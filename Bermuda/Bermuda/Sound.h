#pragma once
#include <SDL_mixer.h>
#include <vector>

class Sound
{
public:
	Sound();
	virtual ~Sound();

	std::vector<Mix_Music*> menuMusic;
	std::vector<Mix_Music*> gameMusic;

	//Mix_Chunk* gChunk[10];
	bool* quit;

	void playMenuMusic();
	void playGameMusic();

private:
	bool init();
};

