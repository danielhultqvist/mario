#include "GameEngine.h"
#include <stdio.h>
#include "../constants/ApplicationConstants.h"
#include "../states/GameStates.h"
#include "../states/StateIncludes.h"
#include "../states/Level1State.h"

GameEngine::GameEngine() 
{
	m_state = NULL;
	m_stateId = STATE_NULL;
	m_nextStateId = STATE_NULL;
	m_textureStore = new TextureStore();
	m_camera = new Camera();
}

GameEngine::~GameEngine()
{
	delete m_player;
	delete m_textureStore;
	delete m_camera;
}

GameEngine& GameEngine::getInstance() 
{
	static GameEngine instance;
	return instance;
}

/**
 * Starts game engine, creates window and renderer
 */
int GameEngine::init() 
{
	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, Mario::SCREEN_WIDTH, Mario::SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL )
	{
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return Mario::STATUS_FATAL;
	}
	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	if (renderer == NULL) 
	{
		printf( "Could not create renderer. SDL_Error: %s\n", SDL_GetError() );
		return Mario::STATUS_FATAL;
	}
	// Set render draw color to WHITE
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	set_next_state(STATE_INIT);
	changeState();

	return Mario::STATUS_OK;
}

void GameEngine::startNewGame()
{
	delete m_player;
	delete m_camera;
	m_player = new Player(100,600);
	m_camera = new Camera();
}

Player* GameEngine::getCurrentPlayer()
{
	return m_player;
}

TextureStore* GameEngine::getTextureStore()
{
	return m_textureStore;
}

SDL_Surface* GameEngine::getScreenSurface() 
{
	return SDL_GetWindowSurface( window );
}

SDL_Window* GameEngine::getWindow() 
{
	return window;
}

SDL_Renderer* GameEngine::getRenderer() 
{
	return renderer;
}

Camera* GameEngine::getCamera()
{
	return m_camera;
}

void GameEngine::set_next_state(int state) 
{
	// Exit state has highest priority, dont escape it
	if( m_nextStateId != STATE_EXIT ) 
	{
		m_nextStateId = state;
	}
}

int GameEngine::getStateId()
{
	return m_stateId;
}

GameState* GameEngine::getState() 
{
	return m_state;
}

void GameEngine::changeState()
{
	if (m_nextStateId != STATE_NULL)
	{
		if (m_nextStateId != STATE_EXIT) 
		{
			delete m_state;
		}
		switch( m_nextStateId )
		{
			case STATE_INIT:
				m_state = new InitState();
				break;

			case STATE_MAIN_MENU:
				m_state = new MainMenuState();
				break;

			case STATE_SETTINGS:
				m_state = new SettingsState();
				break;

			case STATE_LEVEL_1:
				m_state = new Level1State();
				break;
		}
		m_stateId = m_nextStateId;
		m_nextStateId = STATE_NULL;
	}
}

void GameEngine::shutdown() 
{
	//Destroy window
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
}