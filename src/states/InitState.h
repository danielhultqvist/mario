#ifndef INIT_STATE_H
#define INIT_STATE_H

#include <SDL.h>
#include "GameState.h"
#include <SDL_mixer.h>

class InitState : public GameState 
{
public:
	InitState();
	~InitState();

	void handle_events();
	void logic();
	void render();

private:
	SDL_Texture* background;
	Mix_Chunk* intro;
	bool playIntro;
};

#endif