#include "TextureStore.h"
#include "../helpers/GraphicsHelper.h"

typedef std::map<std::string, SDL_Surface*>::iterator surface_iterator;
typedef std::map<std::string, SDL_Texture*>::iterator texture_iterator;

TextureStore::~TextureStore()
{
	for(surface_iterator it = m_surfaces.begin(); it != m_surfaces.end(); it++)
	{
		SDL_FreeSurface(it->second);
	}
	for(texture_iterator it = m_textures.begin(); it != m_textures.end(); it++)
	{
		SDL_DestroyTexture(it->second);
	}
}


bool TextureStore::surfaceIsNotLoaded(std::string path)
{
	return m_surfaces.find(path) == m_surfaces.end();
}

SDL_Surface* TextureStore::getOrLoadSurface(std::string filePath)
{
	if (surfaceIsNotLoaded(filePath))
	{
		m_surfaces[filePath] = GraphicsHelper::loadSurface(filePath);
	}
	return m_surfaces[filePath];
}

bool TextureStore::textureIsNotLoaded(std::string path)
{
	return m_textures.find(path) == m_textures.end();
}

SDL_Texture* TextureStore::getOrLoadTexture(std::string filePath)
{
	if (textureIsNotLoaded(filePath))
	{
		m_textures[filePath] = GraphicsHelper::loadTexture(filePath);
	}
	return m_textures[filePath];
}