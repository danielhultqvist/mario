#ifndef SETTINGS_STATE_H
#define SETTINGS_STATE_H

#include <SDL.h>
#include "GameState.h"

enum class SettingsOption
{
	OPTION_MUSIC,
	OPTION_EFFECTS,
	OPTION_SUBTITLES,
	OPTION_SAVE,
	OPTION_EXIT
};

class SettingsState : public GameState 
{
public:
	SettingsState();
	~SettingsState();

	void handle_events();
	void logic();
	void render();

private:
	SDL_Texture* background;
	SDL_Texture* star;
	int m_selectedOption;
	const int m_numOptions;

	void loadSettings();
	void saveSettings();

	bool selectionIsOnUpperPart();
	void moveSelectionUp();
	void moveSelectionDown();
	void selectOption();
	SDL_Rect createStartRenderBox();
};

#endif