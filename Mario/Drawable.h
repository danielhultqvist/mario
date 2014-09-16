#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SDL.h>

class Drawable {
public:
	virtual void draw(SDL_Surface* surface) = 0;
};

#endif DRAWABLE_H