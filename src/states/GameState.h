#ifndef GAME_STATE_H
#define GAME_STATE_H

class GameState
{
public:
	virtual void handle_events() = 0;
	virtual void logic() = 0;
	virtual void render() = 0;
	virtual ~GameState() {}
};

#endif