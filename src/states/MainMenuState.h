#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include <SDL.h>
#include "GameState.h"
#include <SDL_mixer.h>

enum class MainMenuOption
{
	OPTION_START,
	OPTION_SETTINGS,
	OPTION_EXIT
};

class MainMenuState : public GameState 
{
public:
	MainMenuState();
	~MainMenuState();

	void handle_events();
	void logic();
	void render();

	void moveSelectionUp();
	void moveSelectionDown();
	SDL_Rect createStartRenderBox();
	void selectOption();

private:
	SDL_Texture* m_background;
	SDL_Texture* m_star;
	int m_selectedOption;
};

#endif