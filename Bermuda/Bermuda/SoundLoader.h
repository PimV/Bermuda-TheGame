#pragma once
#include <SDL_mixer.h>
#include <vector>

enum class StateType;

class SoundLoader
{
public:
	SoundLoader();
	virtual ~SoundLoader();

	void playMenuMusic();
	void playGameMusic();
	void closeMusic();

	static SoundLoader* Instance() {
		return &m_SoundLoader;
	};
private:
	bool initialiseSound();
	void initialiseThread();

	bool loadMenuMusic();
	bool loadGameMusic();

	void threadMusic();

	std::vector<Mix_Music*> menuMusic;
	std::vector<Mix_Music*> gameMusic;
	//std::vector<Mix_Chunk*> soundEffects;

	int target_time_ms;
	bool quit;
	bool haltMusic;
	static SoundLoader m_SoundLoader;

	StateType stateType;
};