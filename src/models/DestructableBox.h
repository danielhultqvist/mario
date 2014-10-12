#ifndef DESTRUCTABLE_BOX_H
#define DESTRUCTABLE_BOX_H

#include "Destructable.h"
#include <string>
#include <vector>
#include <deque>

class DestructableBox : public Destructable
{
public:
	DestructableBox(std::deque<std::string> values);
	SDL_Rect getBoundingBox();
	SDL_Rect getBoundingBox(int offsetX, int offsetY);
	void draw();
	void draw(int offsetX, int offsetY);

	int getX() { return m_x; }
	int getY() { return m_y; }
	int getW() { return m_w; }
	int getH() { return m_h; }
	std::string getTexturePath() { return m_texture_path; }

private:
	int m_x, m_y, m_w, m_h;
	std::string m_texture_path;
	SDL_Surface* m_texture;

	SDL_Rect createBoundingBox();
};

#endif