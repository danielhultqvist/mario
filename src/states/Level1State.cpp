#include "../models/MapEditor.h"
#include "../helpers/GraphicsHelper.h"
#include "../helpers/SoundHelper.h"
#include "../engine/GameEngine.h"
#include "../engine/MapFactory.h"
#include "Level1State.h"
#include "GameStates.h"

Level1State::Level1State()
{
	m_background = GraphicsHelper::loadTexture("resources/images/level1-bg.png");
	m_backgroundMusic = SoundHelper::loadMusic("resources/sounds/level1_x.ogg");
	m_map = MapFactory().createLevel1();
	m_editor = MapEditor(m_map);
	
	Mix_PlayMusic(m_backgroundMusic, 0);
	setStartPoint();
}

Level1State::~Level1State()
{
	SDL_DestroyTexture(m_background);
	Mix_FreeMusic(m_backgroundMusic);
	delete m_map;
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
		if ( eventIsMapEditorEvent(event) )
		{
			m_editor.handleEvent(event);
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

bool Level1State::eventIsMapEditorEvent(SDL_Event& event)
{
	return event.type == SDL_MOUSEBUTTONDOWN || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s);
}

void Level1State::logic()
{
	GameEngine::getInstance().getCurrentPlayer()->update(m_map);
}

void Level1State::render()
{
	SDL_RenderCopy(GameEngine::getInstance().getRenderer(), m_background, NULL, NULL);
	GameEngine::getInstance().getCurrentPlayer()->draw(m_map);
	m_map->draw(GameEngine::getInstance().getScreenSurface());
}