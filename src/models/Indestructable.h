#ifndef INDESTRUCTABLE_H
#define INDESTRUCTABLE_H

#include "Drawable.h"
#include "Collidable.h"

class Indestructable : public Drawable, public Collidable
{
public:
	virtual ~Indestructable() {};
	virtual void draw() {}
	virtual void draw(int offsetX, int offsetY) {}
};

#endif