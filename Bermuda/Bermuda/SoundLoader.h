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
	bool loadMenuMusic();
	bool loadGameMusic();

	void threadMenuMusic(std::vector<Mix_Music*> menuMusic);
	static int threadGameMusic(void* data);

	std::vector<Mix_Music*> menuMusic;
	std::vector<Mix_Music*> gameMusic;
	//std::vector<Mix_Chunk*> soundEffects;

	bool* quit;

	static bool init();
};

