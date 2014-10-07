#ifndef MAP_H
#define MAP_H

#include <SDL.h>
#include <vector>
#include "Enemy.h"
#include "Destructable.h"
#include "Indestructable.h"
#include "MapLineEntry.h"
#include <limits>

const int MAX_INT = std::numeric_limits<int>::max();
const int MIN_INT = std::numeric_limits<int>::min();

class MapBounds
{
public:
	MapBounds() {left = MIN_INT; right = MAX_INT; top = MIN_INT; bottom = MAX_INT; }
	MapBounds(std::deque<std::string> values);
	int left, right, top, bottom;
};

class Map
{
public:
	Map();
	~Map();
	void draw(SDL_Surface* surface);
	std::vector<Indestructable*>& getIndestructables();
	std::vector<Destructable*>& getDestructables();
	void processEntry(MapLineEntry entry);
	void clearAll();
	bool lineShouldBeProcessed(std::string line);
	Map loadFromFile(std::string filePath);
	MapBounds getOuterBounds();

private:
	std::vector<Indestructable*> m_indestructables;
	std::vector<Destructable*> m_destructables;
	std::vector<Enemy*> m_enemies;
	MapBounds m_outerBounds;
};

#endif