#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>
#include <SDL_mixer.h>
#include <string>
#include "Drawable.h"
#include "Collidable.h"
#include "Enemy.h"
#include "Indestructable.h"
#include "Destructable.h"
#include <vector>
#include "Map.h"
#include "MovementVector.h"
#include "CollisionPoint.h"
#include "../engine/CollisionDetector.h"
#include "../engine/Camera.h"

const std::string player_image_path = "resources/images/player.png";
const std::string player_texture_path = "resources/images/player.png";


class Player : public Collidable
{
public:

	;
	Player(int x, int y);
	~Player();

	void handle_event(SDL_Event& event);

	void draw(Map* map);
	void handleOuterBounds(Map* map);
	void update(Map* map);
	SDL_Rect getBoundingBox();
	SDL_Rect getBoundingBox(Map* map);
	MovementVector& getMovementVector();
	void moveTo(int x, int y);
private:
	Mix_Chunk* m_jumpSound;
	const int m_speed;
	std::vector<CollisionPoint> collisionPoints;
	int m_x, m_y, m_w, m_h;
	bool m_airbourne;
	MovementVector movementVector;
	void handleIndestructableCollisions(std::vector<Indestructable*> indestructables, Camera* camera);
	void handleDestructableCollisions(std::vector<Destructable*> destructables, Camera* camera);
};

#endif PLAYER_H