#include "Timer.h"
#include <SDL.h>

Timer::Timer() 
{
	stop();
}

void Timer::start() 
{
	m_started = true;
	m_paused = false;
	m_startTicks = SDL_GetTicks();
	m_pausedTicks = 0;
}

void Timer::stop() 
{
	m_paused = false;
	m_started = false;
	m_startTicks = 0;
	m_pausedTicks = 0;
}

void Timer::pause() 
{
	if( m_started && !m_paused ) 
	{
		m_paused = true;
		m_pausedTicks = SDL_GetTicks() - m_startTicks;
		m_startTicks = 0;
	}
}

void Timer::unpause() 
{
	if( m_started && m_paused ) 
	{
		m_paused = false;
		m_startTicks = SDL_GetTicks() - m_pausedTicks;
		m_pausedTicks = 0;
	}
}

unsigned int Timer::getTicks() 
{
	if (m_started && m_paused) 
	{
		return m_pausedTicks;
	} 
	else if (m_started)
	{
		return SDL_GetTicks() - m_startTicks;
	}
	return 0;
}

bool Timer::isStarted()
{
	return m_started;
}

bool Timer::isPaused() 
{
	return m_paused && m_started;
}