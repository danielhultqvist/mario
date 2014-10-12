#include "SoundHelper.h"

Mix_Chunk* SoundHelper::loadChunk(std::string filePath)
{
	Mix_Chunk* res = Mix_LoadWAV(filePath.c_str());
	if (res == NULL)
	{
		std::cout << "Unable to load wav file " << filePath.c_str();
	}
	return res;
}

Mix_Music* SoundHelper::loadMusic(std::string filePath)
{
	Mix_Music* res = Mix_LoadMUS(filePath.c_str());
	return res;
}