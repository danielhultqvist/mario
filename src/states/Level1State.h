#ifndef LEVEL_1_STATE
#define LEVEL_1_STATE

#include <SDL.h>
#include <SDL_mixer.h>
#include "GameState.h"
#include "../models/Map.h"

class Level1State : public GameState 
{
public:
	Level1State();
	~Level1State();

	void handle_events();
	void logic();
	void render();

private:
	SDL_Texture* background;
	Mix_Music* backgroundMusic;
	Map* map;

	void setStartPoint();
	bool eventIsQuit(SDL_Event& event);
};

#endif