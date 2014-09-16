#include <SDL.h>
#include <vector>
#include "Drawable.h"
#include "Player.h"
#include <stdio.h>
#include "ApplicationConstants.h"

void cleanResources(std::vector<Drawable*> drawables) {
	for(int i = 0; i < drawables.size(); ++i) {
		delete drawables[i];
	}
}

int main( int argc, char* args[] )
{
	//The window we'll be rendering to
	SDL_Window* window = NULL;
	
	//The surface contained by the window
	SDL_Surface* screenSurface = NULL;

	std::vector<Drawable*> drawables;

	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
	}
	else
	{
		//Create window
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL )
		{
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		}
		else
		{
			std::vector<Drawable*> drawables;
			drawables.push_back(new Player(10,10));

			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );

            //Fill the surface white
            SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) );

			for(int i = 0; i < drawables.size(); ++i) {
				drawables[i]->draw(screenSurface);
			}

			//Update the surface
			SDL_UpdateWindowSurface( window );

			//Wait two seconds
			SDL_Delay( 2000 );
		}
	}

	//Destroy window
	SDL_DestroyWindow( window );

	cleanResources(drawables);

	//Quit SDL subsystems
	SDL_Quit();

	return 0;
}