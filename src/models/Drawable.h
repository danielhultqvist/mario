#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <SDL.h>
#include <string>

class Drawable {
public:
	virtual ~Drawable() {};
	virtual void draw() = 0;
	virtual std::string getTexturePath() = 0;
};

#endif DRAWABLE_H