#include "Player.h"
#include <iostream>

Player::Player(int x, int y) : m_x(x), m_y(y) {
	player_surface = SDL_LoadBMP( player_texture.c_str() );
	if( player_surface == NULL )
    {
        printf( "Unable to load image: %s" , SDL_GetError() );
    }
}

Player::~Player() {
	std::cout << "Destroying player";
	SDL_FreeSurface(player_surface);
}

void Player::draw(SDL_Surface* surface) {
	SDL_BlitSurface(player_surface, NULL, surface, NULL);
}