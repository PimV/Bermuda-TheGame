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
	void closeMusic();
private:
	bool init();

	bool loadMenuMusic();
	bool loadGameMusic();
	void threadMenuMusic();
	void threadGameMusic();

	std::vector<Mix_Music*> menuMusic;
	std::vector<Mix_Music*> gameMusic;
	//std::vector<Mix_Chunk*> soundEffects;

	int target_time_ms;
	bool quit;
};

