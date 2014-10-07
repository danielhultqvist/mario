#include "CollisionDetector.h"

bool CollisionDetector::checkCollision(Collidable* a, Collidable* b)
{
	SDL_Rect a_boundingbox = a->getBoundingBox();
	int topA = a_boundingbox.y;
	int bottomA  = a_boundingbox.y + a_boundingbox.h;
	int leftA = a_boundingbox.x;
	int rightA  = a_boundingbox.x + a_boundingbox.w;

	SDL_Rect b_boundingbox = b->getBoundingBox();
	int topB = b_boundingbox.y;
	int bottomB  = b_boundingbox.y + b_boundingbox.h;
	int leftB = b_boundingbox.x;
	int rightB  = b_boundingbox.x + b_boundingbox.w;

	if (bottomA <= topB)
	{
		return false;
	}
	if (bottomB <= topA)
	{
		return false;
	}
	if (rightA <= leftB)
	{
		return false;
	}
	if (rightB <= leftA)
	{
		return false;
	}
	return true;
}

bool CollisionDetector::checkCollision(CollisionPoint p, Collidable* a)
{
	SDL_Rect a_boundingbox = a->getBoundingBox();
	int topA = a_boundingbox.y;
	int bottomA  = a_boundingbox.y + a_boundingbox.h;
	int leftA = a_boundingbox.x;
	int rightA  = a_boundingbox.x + a_boundingbox.w;

	if (p.x < leftA)
	{
		return false;
	}
	if (p.x > rightA)
	{
		return false;	
	}
	if (p.y > bottomA) 
	{
		return false;
	}
	if (p.y < topA) 
	{
		return false;
	}
	return true;
}

bool CollisionDetector::checkCollision(CollisionPoint p, Collidable* a, Camera* camera)
{
	SDL_Rect a_boundingbox = a->getBoundingBox();
	int topA = a_boundingbox.y;
	int bottomA  = a_boundingbox.y + a_boundingbox.h;
	int leftA = a_boundingbox.x; // + camera->getOffsetX();
	int rightA  = a_boundingbox.x + a_boundingbox.w; // + camera->getOffsetX();

	if (p.x < leftA)
	{
		return false;
	}
	if (p.x > rightA)
	{
		return false;	
	}
	if (p.y > bottomA) 
	{
		return false;
	}
	if (p.y < topA) 
	{
		return false;
	}
	return true;

}