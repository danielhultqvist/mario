#include "MapEditor.h"
#include <fstream>
#include "../../src/engine/GameEngine.h"
#include "../../src/models/IndestructableBox.h"
#include "../../src/helpers/StringUtils.h"
#include "../../src/models/DestructableBox.h"

MapEditor::MapEditor(Map* map)
{
	this->map = map;
}

void MapEditor::printHeader(std::ofstream& stream)
{
	stream << "# ------------------------------------------------" << std::endl;
	stream << "# LINES STARTING WITH '#' ARE REGARDED AS COMMENTS" << std::endl;
	stream << "#" << std::endl;
	stream << "# TYPES:" << std::endl;
	stream << "# -----------------------" << std::endl;
	stream << "# INDESTRUCTABLE_BOX;X;Y;W;H;TEXTURE_PATH" << std::endl;
	stream << "# DESTRUCTABLE_BOX;X;Y;W;H;TEXTURE_PATH" << std::endl;
	stream << "# OUTER_BOUNDS;TOP;BOTTOM;LEFT;RIGHT" << std::endl;
	stream << "# ------------------------------------------------" << std::endl << std::endl;
}

void MapEditor::printIndestructables(std::ofstream& stream)
{
	// INDESTRUCTABLE_BOX;X;Y;W;H;TEXTURE_PATH
	std::vector<Indestructable*> indestructables = map->getIndestructables();
	for(int i = 0; i < indestructables.size(); ++i)
	{
		Indestructable* box = indestructables.at(i);
		SDL_Rect bb = box->getBoundingBox();
		stream << "INDESTRUCTABLE_BOX;" << bb.x << ";" << bb.y << ";" << bb.w << ";" << bb.h << ";" << box->getTexturePath() << std::endl;
	}
	stream << std::endl;
}

void MapEditor::printDestructables(std::ofstream& stream)
{
	// DESTRUCTABLE_BOX;X;Y;W;H;TEXTURE_PATH
	std::vector<Destructable*> destructables = map->getDestructables();
	for(int i = 0; i < destructables.size(); ++i)
	{
		Destructable* box = destructables.at(i);
		SDL_Rect bb = box->getBoundingBox();
		stream << "DESTRUCTABLE_BOX;" << bb.x << ";" << bb.y << ";" << bb.w << ";" << bb.h << ";" << box->getTexturePath()  << std::endl;
	}
	stream << std::endl;
}

void MapEditor::printBounds(std::ofstream& stream)
{
	// OUTER_BOUNDS;TOP;BOTTOM;LEFT;RIGHT
	MapBounds bounds = map->getOuterBounds();
	stream << "OUTER_BOUNDS" << ";";
	stream << bounds.top << ";";
	stream << bounds.bottom << ";";
	stream << bounds.left << ";";
	stream << bounds.right << std::endl;
	stream << std::endl;
}

void MapEditor::saveMap(std::string file)
{
	std::ofstream mapfile (file);
	if (mapfile.is_open())
	{
		printHeader(mapfile);
		printIndestructables(mapfile);
		printDestructables(mapfile);
		printBounds(mapfile);
		mapfile.flush();
		mapfile.close();
	} 
	else
	{
		std::cout << "Unable to save file, could not open file";
	}
}

void MapEditor::createIndestructable(SDL_Event& event)
{
	Camera* camera = GameEngine::getInstance().getCamera();
	int x = event.button.x - camera->getOffsetX();
	int y = event.button.y - camera->getOffsetY();
	std::deque<std::string> values;
	values.push_back(StringUtils::convertInt(x - x % 40));
	values.push_back(StringUtils::convertInt(y - y % 40));
	values.push_back("40");
	values.push_back("40");
	values.push_back("brick.png");

	IndestructableBox* box = new IndestructableBox(values);
	map->getIndestructables().push_back(box);
}

void MapEditor::createDestructable(SDL_Event& event)
{
	Camera* camera = GameEngine::getInstance().getCamera();
	int x = event.button.x - camera->getOffsetX();
	int y = event.button.y - camera->getOffsetY();
	std::deque<std::string> values;
	values.push_back(StringUtils::convertInt(x - x % 40));
	values.push_back(StringUtils::convertInt(y - y % 40 + 8)); // + 8 just because
	values.push_back("40");
	values.push_back("40");
	values.push_back("wood-box.png");

	DestructableBox* box = new DestructableBox(values);
	map->getDestructables().push_back(box);
}

void MapEditor::handleEvent(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_s)
	{
		saveMap("test.txt");
	}
	// temporary
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT ) 
	{
		createIndestructable(event);
	}
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_RIGHT )
	{
		createDestructable(event);
	}
}