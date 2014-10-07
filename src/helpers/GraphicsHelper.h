#ifndef GRAPHICSHELPER_H
#define GRAPHICSHELPER_H

#include <iostream>
#include <string>
#include <SDL.h>
#include <SDL_image.h>

class GraphicsHelper 
{
public:
	static SDL_Surface* loadSurface( std::string path );
	static SDL_Texture* loadTexture( std::string path );

private:
	static SDL_Surface* loadSurfaceSimple( std::string path );
};

#endif GRAPHICSHELPER_H