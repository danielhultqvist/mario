#ifndef COLLISION_POINT_H
#define COLLISION_POINT_H

enum CollisionPointType 
{
	HEAD,
	FEET,
	LEFT,
	RIGHT
};

class CollisionPoint
{
public:
	CollisionPoint(int x, int y, CollisionPointType type) { this->x = x; this->y = y; this->type = type; }
	int x, y;	
	CollisionPointType type;
};

#endif