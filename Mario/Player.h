#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <string>
#include "Drawable.h"

const std::string player_texture = "player.bmp";

class Player : public Drawable {
public:
	Player(int x, int y);
	~Player();

	void draw(SDL_Surface* surface);

private:
	int m_x, m_y;
	SDL_Surface* player_surface;
};

#endif PLAYER_H