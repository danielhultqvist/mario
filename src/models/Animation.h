#ifndef ANIMATION_H
#define ANIMATION_H
#include <vector>
#include <SDL.h>

class Animation
{
public:
	Animation();
	void addStep(int x, int y, int w, int h);
	void increaseDelta();
	void increaseStep();
	SDL_Rect getStep();
	SDL_Rect getStepAndIncrease();
	void setStepDelta(int delta);
	void setCircular(bool circular);
	void reset();

private:
	std::vector<SDL_Rect> m_steps;
	bool m_circular;
	int m_currentStep;
	int m_delta, m_currentDelta;
};

#endif