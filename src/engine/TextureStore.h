#ifndef TEXTURE_STORE_H
#define TEXTURE_STORE_H

#include <SDL.h>
#include <string>
#include <map>

class TextureStore
{
public:
	~TextureStore();
	bool surfaceIsNotLoaded(std::string path);
	bool textureIsNotLoaded(std::string path);
	SDL_Surface* getOrLoadSurface(std::string filePath);
	SDL_Texture* getOrLoadTexture(std::string filePath);

private:
	std::map<std::string, SDL_Surface*> m_surfaces;
	std::map<std::string, SDL_Texture*> m_textures;
};


#endif 