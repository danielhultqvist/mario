#ifndef MAP_EDITOR_H
#define MAP_EDITOR_H

#include <string>
#include "../../src/models/Map.h"

class MapEditor
{
public:
	MapEditor() {}
	MapEditor(Map* map);
	void printHeader(std::ofstream& stream);
	void printIndestructables(std::ofstream& stream);
	void printDestructables(std::ofstream& stream);
	void printBounds(std::ofstream& stream);
	void saveMap(std::string file);
	void createIndestructable(SDL_Event& event);
	void createDestructable(SDL_Event& event);
	void handleEvent(SDL_Event& event);

private:
	Map* map;
};

#endif