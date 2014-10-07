#ifndef SOUND_HELPER_H
#define SOUND_HELPER_H

#include <SDL_mixer.h>
#include <iostream>

class SoundHelper
{
public:
	static Mix_Chunk* loadChunk(std::string filePath);
	static Mix_Music* loadMusic(std::string filePath);
};

#endif