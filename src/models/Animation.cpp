#include "Animation.h"

Animation::Animation()
{
	m_currentStep = 0;
	m_currentDelta = 0;
	m_delta = 1;
	m_circular = true;
}

void Animation::addStep(int x, int y, int w, int h)
{
	SDL_Rect step = { x, y, w, h };
	m_steps.push_back(step);
}

void Animation::increaseDelta()
{
	if (m_currentDelta++ >= m_delta)
	{
		m_currentDelta = 0;
		increaseStep();
	}
}

void Animation::increaseStep()
{
	if (++m_currentStep == m_steps.size())
	{
		m_currentStep = m_circular ? 0 : m_steps.size()-1;
	}
}

SDL_Rect Animation::getStep()
{
	return m_steps[m_currentStep];
}

SDL_Rect Animation::getStepAndIncrease()
{
	SDL_Rect currentStep = m_steps[m_currentStep];
	increaseDelta();
	return currentStep;
}

void Animation::setStepDelta(int delta)
{
	m_delta = delta;
}

void Animation::setCircular(bool circular)
{
	m_circular = circular;
}

void Animation::reset()
{
	m_currentStep = 0;
	m_currentDelta = 0;
}