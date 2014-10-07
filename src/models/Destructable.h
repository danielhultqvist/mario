#ifndef DESTRUCTABLE_H
#define DESTRUCTABLE_H

#include "Drawable.h"
#include "Collidable.h"

class Destructable : public Drawable, public Collidable
{
public:
	virtual ~Destructable() {};
	virtual void draw() {}
	virtual void draw(int offsetX, int offsetY) {}
};

#endif