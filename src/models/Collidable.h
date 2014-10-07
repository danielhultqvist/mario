#ifndef COLLIDABLE_H
#define COLLIDABLE_H
#include <SDL.h>

class Collidable
{
public:
	virtual SDL_Rect getBoundingBox() = 0;
};

#endif