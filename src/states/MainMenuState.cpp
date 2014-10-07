#include "MainMenuState.h"
#include "../helpers/GraphicsHelper.h"
#include "GameStates.h"
#include <math.h>
#include "../engine/GameEngine.h"

MainMenuState::MainMenuState() 
{
	background = GraphicsHelper::loadTexture("resources/images/mainmenu.png");
	star = GraphicsHelper::loadTexture("resources/images/star.png");
	m_selectedOption = 0;
}

MainMenuState::~MainMenuState()
{
	SDL_DestroyTexture(background);
	SDL_DestroyTexture(star);
}

void MainMenuState::moveSelectionUp()
{
	m_selectedOption = std::max(0, --m_selectedOption);
}

void MainMenuState::moveSelectionDown()
{
	m_selectedOption = std::min(2, ++m_selectedOption);	
}

void MainMenuState::handle_events() 
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

void MainMenuState::logic() 
{

}

void MainMenuState::selectOption()
{
	switch ( m_selectedOption )
	{
		case MainMenuOption::OPTION_START:
			GameEngine::getInstance().startNewGame();
			GameEngine::getInstance().set_next_state( STATE_LEVEL_1 );
			break;

		case MainMenuOption::OPTION_SETTINGS:
			GameEngine::getInstance().set_next_state( STATE_SETTINGS );
			break;

		case MainMenuOption::OPTION_EXIT:
			GameEngine::getInstance().set_next_state( STATE_EXIT );
			break;
	}
}

SDL_Rect MainMenuState::createStartRenderBox()
{
	// star offset 
	int starHeightOffset = 360;
	int starWidthOffset= 35;
	int optionMargin = 65;
	SDL_Rect rect;
	rect.x = starWidthOffset;
	rect.w = 54;
	rect.h = 51;
	rect.y = starHeightOffset + m_selectedOption * optionMargin;
	return rect;
}

void MainMenuState::render()
{
	SDL_RenderCopy(GameEngine::getInstance().getRenderer(), background, NULL, NULL);
	SDL_RenderCopy(GameEngine::getInstance().getRenderer(), star, NULL, &createStartRenderBox());
}