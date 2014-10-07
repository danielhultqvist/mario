#ifndef GAME_ENGINE_H
#define GAME_ENGINE_H

#include <SDL.h>
#include "../states/GameState.h"
#include "../models/Player.h"
#include "TextureStore.h"
#include "Camera.h"

class GameEngine 
{
public:
	static GameEngine& getInstance();
	int init();

	SDL_Surface* getScreenSurface();
	SDL_Window* getWindow();
	SDL_Renderer* getRenderer();
	Camera* getCamera();

	void set_next_state( int state );
	int getStateId();
	GameState* getState();
	void changeState();
	void startNewGame();
	Player* getCurrentPlayer();
	TextureStore* getTextureStore();

	void shutdown();

private: 
	SDL_Window* window;
	SDL_Renderer* renderer;
	int m_stateId, m_nextStateId;
	GameState* m_state;
	Player* m_player;
	TextureStore* m_textureStore;
	Camera* m_camera;

	GameEngine();
	~GameEngine();
	GameEngine(GameEngine const&);
	void operator=(GameEngine const&);
};

#endif GAME_ENGINE_H