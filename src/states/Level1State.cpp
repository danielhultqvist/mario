#include "Level1State.h"
#include "../helpers/GraphicsHelper.h"
#include "../helpers/SoundHelper.h"
#include "GameStates.h"
#include "../engine/GameEngine.h"
#include "../engine/MapFactory.h"

Level1State::Level1State()
{
	background = GraphicsHelper::loadTexture("resources/images/level1-bg.png");
	backgroundMusic = SoundHelper::loadMusic("resources/sounds/level1-music.wav");
	setStartPoint();
	MapFactory factory;
	map = factory.createLevel1();
}

Level1State::~Level1State()
{
	SDL_DestroyTexture(background);
	Mix_FreeMusic(backgroundMusic);
	delete map;
}

void Level1State::setStartPoint()
{
	GameEngine::getInstance().getCurrentPlayer()->moveTo(100, 500);
}

void Level1State::handle_events()
{
	SDL_Event event;
	while( SDL_PollEvent( &event ) ) 
	{
		if( eventIsQuit(event) ) 
		{
			GameEngine::getInstance().set_next_state( STATE_MAIN_MENU );
		}
		else
		{
			GameEngine::getInstance().getCurrentPlayer()->handle_event(event);
		}
	}	
}

bool Level1State::eventIsQuit(SDL_Event& event)
{
	return event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE);
}

void Level1State::logic()
{
	GameEngine::getInstance().getCurrentPlayer()->update(map);
}

void Level1State::render()
{
	SDL_RenderCopy(GameEngine::getInstance().getRenderer(), background, NULL, NULL);
	GameEngine::getInstance().getCurrentPlayer()->draw(map);
	map->draw(GameEngine::getInstance().getScreenSurface());
}