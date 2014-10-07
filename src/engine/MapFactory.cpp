#include "MapFactory.h"
#include "../models/IndestructableBox.h"

Map* MapFactory::createLevel1()
{
	Map* level1 = new Map();
	level1->loadFromFile("resources/levels/level1.map");
	return level1;
}