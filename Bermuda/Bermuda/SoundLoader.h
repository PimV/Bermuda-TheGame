#pragma once
#include <SDL_mixer.h>
#include <vector>

class SoundLoader
{
public:
	SoundLoader();
	virtual ~SoundLoader();

	void playMenuMusic();
	void playGameMusic();

private:
	std::vector<Mix_Music*> menuMusic;
	std::vector<Mix_Music*> gameMusic;
	//std::vector<Mix_Chunk*> soundEffects;

	bool* quit;

	bool init();
};

