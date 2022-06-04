#include "Sound.h"

Sound* Sound::pInstance = NULL;
Sound::~Sound()
{

}

void Sound::PlaySound(Mix_Chunk* Chunk, int channel, int repeat)
{
	Mix_PlayChannel(channel, Chunk, repeat);
}

void Sound::CancelChannel(int channel)
{
	Mix_HaltChannel(channel);
}

void Sound::PauseChannel(int channel)
{
	Mix_Pause(channel);
}

void Sound::resumeChannel(int channel)
{
	Mix_Resume(channel);
}

void Sound::fadeIN(Mix_Chunk* Chunk, int channel, int repeat, int ms)
{
	Mix_FadeInChannel(channel, Chunk, repeat, ms);
}

void Sound::fadeINTime(Mix_Chunk* Chunk, int channel, int repeat, int ms, int ticks)
{
	Mix_FadeInChannelTimed(channel, Chunk, repeat, ms, ticks);
}

Sound::Sound() {
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
