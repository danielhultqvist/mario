#ifndef INDESTRUCTABLE_BOX_H
#define INDESTRUCTABLE_BOX_H
#include "Indestructable.h"
#include <string>
#include <vector>
#include <deque>

class IndestructableBox : public Indestructable
{
public:
	
	IndestructableBox(std::deque<std::string> values);
	
	void draw();
	void draw(int offsetX, int offsetY);
	SDL_Rect getBoundingBox();
	SDL_Rect getBoundingBox(int offsetX, int offsetY);

	int getX() { return m_x; }
	int getY() { return m_y; }
	int getW() { return m_w; }
	int getH() { return m_h; }
	std::string getTexturePath() { return m_texture_path; }

private:
	int m_x, m_y, m_w, m_h;
	std::string m_texture_path;
	SDL_Surface* m_texture;
	bool shouldBeDrawn();
};

#endif