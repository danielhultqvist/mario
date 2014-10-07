#include <SDL.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <tchar.h>
#include <vector>
#include "models/Drawable.h"
#include "models/Player.h"
#include <stdio.h>
#include "constants/ApplicationConstants.h"
#include "helpers/GraphicsHelper.h"
#include <iostream>
#include "engine/GameEngine.h"
#include "states/GameStates.h"
#include "engine/Timer.h"
#include <gtest/gtest.h>
#include "../test/TestRunner.h"

void refreshScreen()
{
	SDL_RenderPresent(GameEngine::getInstance().getRenderer());
}

int initializeSDL() 
{
	//Initialize SDL
	if( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 )
	{
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return -1;
	}
	// Initialize SDL_image
	if ( !(IMG_Init( Mario::IMG_FORMAT ) & Mario::IMG_FORMAT ) )
	{
		printf( "SDL_image could not initialize! SDL_image error: %s\n", IMG_GetError() );
		return -1;
	}
	if ( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0 )
	{
		printf( "SDL_mixer could not initialize! SDL_mixer error: %s\n", Mix_GetError() );
		return -1;	
	}
	return 0;
}

int startGame()
{
	Timer fpsTimer;
	if (initializeSDL() == -1) 
	{
		exit(-1);
	}
	else
	{
		//Create window
		if (GameEngine::getInstance().init() == Mario::STATUS_FATAL) 
		{
			exit(Mario::STATUS_FATAL);
		}
		else
		{
			while( GameEngine::getInstance().getStateId() != STATE_EXIT ) 
			{		
				fpsTimer.start();
				
				GameState* state = GameEngine::getInstance().getState();
				
				state->handle_events();

				state->logic();
				
				state->render();
				
				GameEngine::getInstance().changeState();

				refreshScreen();

				if (fpsTimer.getTicks() < Mario::UPDATE_RATE )
				{
					SDL_Delay ( Mario::UPDATE_RATE - fpsTimer.getTicks() );
				}
			}
		}
	}

	GameEngine::getInstance().shutdown();
	
	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();

	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	// Run tests
	if (argc == 2)
	{
		TestRunner testRunner;
		//return testRunner.runAllTests();
		return testRunner.runTestGroup("PlayerTest");
		//return testRunner.runSingleTest("PlayerTest", "shouldNotPassThroughIndestructableToTheLeft");
	} 
	// Start game
	else
	{
		startGame();
	}
}