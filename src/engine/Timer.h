#ifndef TIMER_H
#define TIMER_H

class Timer
{
public:
	Timer();

	void start();
	void stop();
	void pause();
	void unpause();

	unsigned int getTicks();
	bool isStarted();
	bool isPaused();

private:
	unsigned int m_startTicks;
	unsigned int m_pausedTicks;

	bool m_paused;
	bool m_started;
};

#endif