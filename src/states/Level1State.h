#ifndef LEVEL_1_STATE
#define LEVEL_1_STATE

#include <SDL.h>
#include <SDL_mixer.h>
#include "GameState.h"
#include "../models/Map.h"
#include "../models/MapEditor.h"

class Level1State : public GameState 
{
public:
	
	Level1State();
	~Level1State();

	
	void handle_events();
	void logic();
	void render();

private:
	SDL_Texture* m_background;
	Mix_Music* m_backgroundMusic;
	Map* m_map;
	MapEditor m_editor;

	void setStartPoint();
	bool eventIsQuit(SDL_Event& event);
	bool eventIsMapEditorEvent(SDL_Event& event);
};

#endif