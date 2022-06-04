#pragma once

#include "SDL.h"
#include <vector>
#include <map>
#include <string>
#include "sdl_mixer.h"

class SoundManager
{
	SoundManager();
	static SoundManager* pInstance;
	Sint32 addSound(const char* file);
	std::vector<Mix_Chunk*>	mChunksVector;
	std::map<std::string, Sint32>	mIDMap;
	Uint32 mFirstFreeSlot;
	Uint32 updateFirstFreeSlotChunk();
public:
	~SoundManager();
	static SoundManager* getInstance() {
		if (pInstance == NULL)
			pInstance = new SoundManager();

		return pInstance;
	}
	Sint32 loadAndGetSoundID(const char* file);
	void removeChunk(const char* file);
	std::string getSoundPathByID(Sint32 ID);
	void PlaySound(Sint32 ID, int channel, int repeat);
	void CancelChannel(int channel); //fa un halt del channel
	void PauseChannel(int channel); //pausa el channel
	void resumeChannel(int channel); //reanuda el channel
	void fadeIn(Sint32 ID, int channel, int repeat, int ms); //de fluix a fort
	void graduateVolume(int channel, int volume); //graduar volum, 128 max
	void haltInTime(int channel, int time); //fa un halt despres de un temps
	void fadeOUT(int channel, int time); //de fort a fluix, has de posar temps i el channel ha de estar sonant
	void fadeInTimed(Sint32 ID, int channel, int repeat, int ms, int ticks);
	bool isPlaying(int id) { return !Mix_Playing(id); };
protected:
};

