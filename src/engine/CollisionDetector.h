#ifndef COLLISION_DETECTOR_H
#define COLLISION_DETECTOR_H
#include "../models/Collidable.h"
#include "../models/CollisionPoint.h"
#include "Camera.h"

class CollisionDetector
{
public:
	bool checkCollision(Collidable* a, Collidable* b);
	bool checkCollision(CollisionPoint a, Collidable* b);
	bool checkCollision(CollisionPoint a, Collidable* b, Camera* camera);
};

#endif