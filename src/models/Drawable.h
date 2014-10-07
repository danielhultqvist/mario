#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SDL.h>

class Drawable {
public:
	virtual ~Drawable() {};
	virtual void draw() = 0;
};

#endif DRAWABLE_H