#include "Map.h"
#include "../engine/GameEngine.h"
#include <fstream>
#include <iostream>
#include "MapLineEntry.h"
#include "IndestructableBox.h"
#include "DestructableBox.h"
#include "../helpers/StringUtils.h"
#include "../helpers/Require.h"

const std::string INDESTRUCTABLE_BOX_TYPE = "INDESTRUCTABLE_BOX";
const std::string DESTRUCTABLE_BOX_TYPE = "DESTRUCTABLE_BOX";
const std::string BOUNDS_TYPE = "OUTER_BOUNDS";

Map::Map()
{
	m_indestructables.clear();
	m_destructables.clear();
	m_enemies.clear();
	m_outerBounds = MapBounds();
}

Map::~Map()
{
	for(int i = 0; i < m_indestructables.size(); ++i)
	{
		delete m_indestructables[i];
	}
	for(int i = 0; i < m_destructables.size(); ++i)
	{
		delete m_destructables[i];
	}
	for(int i = 0; i < m_enemies.size(); ++i)
	{
		delete m_enemies[i];
	}
}

void Map::draw(SDL_Surface* surface)
{
	Camera* camera = GameEngine::getInstance().getCamera();
	for(int i = 0; i < m_indestructables.size(); ++i)
	{
		m_indestructables.at(i)->draw(camera->getOffsetX(), camera->getOffsetY());
	}
	for(int i = 0; i < m_destructables.size(); ++i)
	{
		m_destructables.at(i)->draw(camera->getOffsetX(), camera->getOffsetY());
	}
}

std::vector<Indestructable*>& Map::getIndestructables()
{
	return m_indestructables;
}

std::vector<Destructable*>& Map::getDestructables()
{
	return m_destructables;
}

void Map::processEntry(MapLineEntry entry)
{
	if (entry.getType() == INDESTRUCTABLE_BOX_TYPE)
	{
		m_indestructables.push_back(new IndestructableBox(entry.getValues()));
	}
	else if (entry.getType() == DESTRUCTABLE_BOX_TYPE)
	{
		m_destructables.push_back(new DestructableBox(entry.getValues()));
	}
	else if (entry.getType() == BOUNDS_TYPE)
	{
		m_outerBounds = MapBounds(entry.getValues());
	}
	else
	{
		std::cout << "UKNOWN MAP OBJECT TYPE: " << entry.getType() << std::endl;
	}
}

void Map::clearAll()
{
	m_indestructables.clear();
	m_destructables.clear();
	m_enemies.clear();
}

bool Map::lineShouldBeProcessed(std::string line)
{
	return StringUtils::trim(line).length() > 0 && line.at(0) != '#';
}

Map Map::loadFromFile(std::string filePath)
{
	Map result;
	std::string line;
	std::ifstream filestream(filePath);
	clearAll();
	if (filestream.is_open())
	{
		while(getline(filestream, line))
		{
			if (lineShouldBeProcessed(line))
			{
				MapLineEntry entry(line);
				processEntry(entry);	
			}
		}
	}
	else
	{
		std::cout << "Unable to load map " << filePath << std::endl;
	}
	return result;
}

MapBounds Map::getOuterBounds()
{
	return m_outerBounds;
}

MapBounds::MapBounds(std::deque<std::string> values)
{
	Require::equal(values.size(), size_t(4));
	top = atoi(values.at(0).c_str());
	bottom = atoi(values.at(1).c_str());
	left = atoi(values.at(2).c_str());
	right = atoi(values.at(3).c_str());
}