#include "SoundManager.h"
#include "SDL.h"
#include <iostream>

SoundManager* SoundManager::pInstance = NULL;
Sint32 SoundManager::addSound(const char* file)
{
	if (updateFirstFreeSlotChunk() == -1) {
		Mix_Chunk* So = Mix_LoadWAV(file);
		if (So != NULL) {
			mChunksVector.push_back(So);
			mIDMap.insert(std::pair<std::string, int>(file, mChunksVector.size() - 1));
			return (Sint32)mChunksVector.size() - 1;
		}
		else {
			std::cout << "Path incorrecte." << std::endl;
			return 0;
		}
	}
	else {
		Mix_Chunk* So = Mix_LoadWAV(file);
		if (So != NULL) {
			mChunksVector.at(mFirstFreeSlot) = So;
			mIDMap.insert(std::pair<std::string, int>(file, mFirstFreeSlot));
			return mFirstFreeSlot;
		}
		else {
			std::cout << "Path incorrecte." << std::endl;
			return 0;
		}
	}
}

SoundManager::~SoundManager()
{

}

Sint32 SoundManager::loadAndGetSoundID(const char* file)
{
	if (mIDMap.find(file) != mIDMap.end()) {
		return mIDMap.find(file)->second;
	}
	else {
		return addSound(file);
	}
}

Uint32 SoundManager::updateFirstFreeSlotChunk() {
	for (int i = 0; i < mChunksVector.size(); i++)
	{
		if (mChunksVector.at(i) == NULL) {
			return mFirstFreeSlot = i;
		}
	}
	return -1;
}

SoundManager::SoundManager()
{
	mFirstFreeSlot = -1;
	if (SDL_WasInit(SDL_INIT_VIDEO) != 0) {
		SDL_InitSubSystem(SDL_INIT_AUDIO);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
		Mix_AllocateChannels(128);
	}
	else {
		//init video
		SDL_InitSubSystem(SDL_INIT_AUDIO);
		Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
		Mix_AllocateChannels(128);
	}
}

void SoundManager::removeChunk(const char* file) {
	if (mIDMap.find(file) != mIDMap.end()) {
		Mix_FreeChunk(mChunksVector.at(mIDMap.find(file)->second));
		mChunksVector.at(mIDMap.find(file)->second) = NULL;
		mIDMap.erase(mIDMap.find(file));
	}
	else {
		std::cout << "NO EXISTEIX" << std::endl;
	}
}

std::string SoundManager::getSoundPathByID(Sint32 ID) {
	if ((Sint64)mIDMap.size() >= ((Sint64)ID + 1)) {
		for (auto& it : mIDMap) {
			if (it.second == ID) {
				return it.first;
			}
		}
	}
	else {
		std::cout << "ID incorrecte" << std::endl;
		return "ERROR";
	}
}

void SoundManager::PlaySound(Sint32 ID, int channel, int repeat) {
	if ((Sint64)mChunksVector.size() >= ((Sint64)ID + 1)) {
		if (mChunksVector.at(ID) != NULL) {
			Mix_PlayChannel(channel, mChunksVector.at(ID), repeat);
		}
		else {
			std::cout << "NULL SCREENSURFACE" << std::endl;
		}
	}
	else {
		std::cout << "ID INEXISTENT" << std::endl;
	}
}

void SoundManager::CancelChannel(int channel)
{
	Mix_HaltChannel(channel);
}

void SoundManager::PauseChannel(int channel)
{
	Mix_Pause(channel);
}

void SoundManager::resumeChannel(int channel)
{
	Mix_Resume(channel);
}

void SoundManager::fadeIn(Sint32 ID, int channel, int repeat, int ms)
{
	if ((Sint64)mChunksVector.size() >= ((Sint64)ID + 1)) {
		if (mChunksVector.at(ID) != NULL) {
			Mix_FadeInChannel(channel, mChunksVector.at(ID), repeat, ms);
		}
		else {
			std::cout << "NULL SCREENSURFACE" << std::endl;
		}
	}
	else {
		std::cout << "ID INEXISTENT" << std::endl;
	}
}

void SoundManager::graduateVolume(int channel, int volume)
{
	Mix_Volume(channel, volume);
}

void SoundManager::haltInTime(int channel, int time)
{
	Mix_ExpireChannel(channel, time);
}

void SoundManager::fadeOUT(int channel, int time)
{
	Mix_FadeOutChannel(channel, time);
}

void SoundManager::fadeInTimed(Sint32 ID, int channel, int repeat, int ms, int ticks)
{
	if ((Sint64)mChunksVector.size() >= ((Sint64)ID + 1)) {
		if (mChunksVector.at(ID) != NULL) {
			Mix_FadeInChannelTimed(channel, mChunksVector.at(ID), repeat, ms, ticks);
		}
		else {
			std::cout << "NULL SCREENSURFACE" << std::endl;
		}
	}
	else {
		std::cout << "ID INEXISTENT" << std::endl;
	}
}
