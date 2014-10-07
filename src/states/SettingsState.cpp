#include "SettingsState.h"
#include "../helpers/GraphicsHelper.h"
#include "../engine/GameEngine.h"
#include "GameStates.h"
#include "../engine/Settings.h"

SettingsState::SettingsState() : m_selectedOption(0), m_numOptions(4)
{
	background = GraphicsHelper::loadTexture("resources/images/settings.png");
	star = GraphicsHelper::loadTexture("resources/images/star.png");
	m_selectedOption = 0;
	loadSettings();
}

SettingsState::~SettingsState()
{
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(star);
}

void SettingsState::logic()
{
	
}

void SettingsState::render()
{
	SDL_RenderClear(GameEngine::getInstance().getRenderer());
	SDL_RenderCopy(GameEngine::getInstance().getRenderer(), background, NULL, NULL);
	SDL_RenderCopy(GameEngine::getInstance().getRenderer(), star, NULL, &createStartRenderBox());
}

void SettingsState::handle_events()
{
	SDL_Event event;
	while( SDL_PollEvent( &event ) ) 
	{
		if( event.type == SDL_QUIT ) 
		{
			GameEngine::getInstance().set_next_state( STATE_EXIT );
		}
		else if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
		{
			GameEngine::getInstance().set_next_state( STATE_EXIT );
		}
		else if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_UP) 
		{
			moveSelectionUp();
		}
		else if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_DOWN) 
		{
			moveSelectionDown();
		}
		else if( event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_RETURN)
		{
			selectOption();
		}
	}
}

void SettingsState::moveSelectionUp()
{
	m_selectedOption = std::max(0, --m_selectedOption);
}

void SettingsState::moveSelectionDown()
{
	m_selectedOption = std::min(m_numOptions, ++m_selectedOption);	
}

void SettingsState::selectOption()
{
	Settings settings;
	switch ( m_selectedOption )
	{
		case SettingsOption::OPTION_MUSIC:
			settings.loadSettings();
			break;

		case SettingsOption::OPTION_EFFECTS:
			break;

		case SettingsOption::OPTION_SUBTITLES:
			break;

		case SettingsOption::OPTION_SAVE:
			saveSettings();
			GameEngine::getInstance().set_next_state( STATE_MAIN_MENU );
			break;

		case SettingsOption::OPTION_EXIT:
			GameEngine::getInstance().set_next_state( STATE_MAIN_MENU );
			break;
	}
}

SDL_Rect SettingsState::createStartRenderBox()
{
	// star offset 
	int starHeightOffset = 305;
	int starWidthOffset= 30;
	int optionMargin = 65;
	int optionSpaceMargin = 45;
	SDL_Rect rect;
	rect.x = starWidthOffset;
	rect.w = 54;
	rect.h = 51;
	if (selectionIsOnUpperPart())
	{
		rect.y = starHeightOffset + m_selectedOption * optionMargin;
	}
	else
	{
		rect.y = starHeightOffset + m_selectedOption * optionMargin + optionSpaceMargin;
	}
		
	return rect;
}

bool SettingsState::selectionIsOnUpperPart()
{
	return m_selectedOption < 3;
}

void SettingsState::loadSettings()
{
	
}

void SettingsState::saveSettings()
{
	
}