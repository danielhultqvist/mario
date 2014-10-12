#include "GraphicsHelper.h"
#include "../engine/GameEngine.h"

SDL_Surface* GraphicsHelper::loadSurfaceSimple( std::string path ) 
{
	SDL_Surface* result = IMG_Load( path.c_str() );
	if ( result == NULL ) 
	{
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError() );
		return NULL;
	}	
	return result;
}

SDL_Surface* GraphicsHelper::loadSurface( std::string path ) 
{
	SDL_Surface* result = NULL;
	SDL_Surface* tempSurface = loadSurfaceSimple( path );
	SDL_Surface* screenSurface = GameEngine::getInstance().getScreenSurface();
	if (tempSurface != NULL) 
	{
		result = SDL_ConvertSurface( tempSurface, screenSurface->format, NULL );
		if ( result == NULL )
		{
			printf( "Unable to load optimized image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		}
		SDL_FreeSurface(tempSurface); 
	}
	return result;
}

SDL_Texture* GraphicsHelper::loadTexture( std::string path ) 
{
	SDL_Renderer* renderer = GameEngine::getInstance().getRenderer();
	SDL_Texture* result = NULL;
	SDL_Surface* tempResult = loadSurfaceSimple( path );
	if (tempResult != NULL) 
	{
		SDL_SetColorKey( tempResult, SDL_TRUE, SDL_MapRGB( tempResult->format, 0xFF, 0x00, 0xFF ) );
		result = SDL_CreateTextureFromSurface( renderer, tempResult );
		if (result == NULL) 
		{
			printf ("Unable to create texture from %s, SDL_Error: %s\n", path.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(tempResult);
	}
	return result;
}