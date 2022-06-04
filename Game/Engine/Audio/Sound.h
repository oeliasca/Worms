#pragma once
#include "SDL.h"
#include "sdl_mixer.h"

class Sound
{
	static Sound* pInstance;
public:
	~Sound();
	static Sound* getInstance() {
		if (pInstance == NULL)
			pInstance = new Sound();

		return pInstance;
	}
	void PlaySound(Mix_Chunk* Chunk, int channel, int repeat);
	void CancelChannel(int channel);
	void PauseChannel(int channel);
	void resumeChannel(int channel);
	void fadeIN(Mix_Chunk* Chunk, int channel, int repeat, int ms);
	void fadeINTime(Mix_Chunk* Chunk, int channel, int repeat, int ms, int ticks);
protected:
	Sound();
};

