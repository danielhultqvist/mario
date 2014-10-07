#include "InitState.h"
#include "../helpers/GraphicsHelper.h"
#include "GameStates.h"
#include "../engine/GameEngine.h"
#include "../helpers/SoundHelper.h"

InitState::InitState() 
{
	background = GraphicsHelper::loadTexture("resources/images/init.png");
	intro = SoundHelper::loadChunk("resources/sounds/intro.wav");
	playIntro = true;
}

InitState::~InitState()
{
	SDL_DestroyTexture(background);
	Mix_FreeChunk(intro);
}

void InitState::handle_events() 
{
	SDL_Event event;
	while( SDL_PollEvent( &event ) ) 
	{
		if( event.type == SDL_QUIT ) 
		{
			GameEngine::getInstance().set_next_state( STATE_EXIT );
		}
		else if( event.type == SDL_KEYDOWN ) 
		{
			GameEngine::getInstance().set_next_state( STATE_MAIN_MENU );
		}
	}
}

void InitState::logic() 
{
	if (playIntro)
	{
		Mix_Volume(-1, 128);
		Mix_PlayChannel(-1, intro, 0);
		playIntro = false;
	}
}

void InitState::render()
{
	SDL_RenderCopy(GameEngine::getInstance().getRenderer(), background, NULL, NULL);
}