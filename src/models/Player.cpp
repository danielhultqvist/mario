#include "Player.h"
#include <iostream>
#include "../helpers/GraphicsHelper.h"
#include "../engine/GameEngine.h"
#include "../engine/CollisionDetector.h"
#include "../helpers/SoundHelper.h"
#include "../models/Animation.h"

const int PLAYER_WIDTH = 20*2;
const int PLAYER_HEIGHT = 40*2;

Animation Player::createRunRightAnimation()
{
	Animation animation;
	animation.addStep(1, 1, 31, 39);
	animation.addStep(1+(1+31)*1, 1, 31, 39);
	animation.addStep(1+(1+31)*2, 1, 31, 39);
	animation.addStep(1+(1+31)*3, 1, 31, 39);
	animation.addStep(1+(1+31)*4, 1, 31, 39);
	animation.addStep(1+(1+31)*5, 1, 31, 39);
	animation.setCircular(true);
	animation.setStepDelta(3);
	return animation;
}

Animation Player::createRunLeftAnimation()
{
	Animation animation;
	animation.addStep(1, 1+(1+39)*1, 31, 39);
	animation.addStep(1+(1+31)*1, 1+(1+39)*1, 31, 39);
	animation.addStep(1+(1+31)*2, 1+(1+39)*1, 31, 39);
	animation.addStep(1+(1+31)*3, 1+(1+39)*1, 31, 39);
	animation.addStep(1+(1+31)*4, 1+(1+39)*1, 31, 39);
	animation.addStep(1+(1+31)*5, 1+(1+39)*1, 31, 39);
	animation.setCircular(true);
	animation.setStepDelta(3);
	return animation;
}

Player::Player(int x, int y) : m_speed(9) 
{
	m_w = PLAYER_WIDTH;
	m_h = PLAYER_HEIGHT;
	movementVector.x = x;
	movementVector.y = y;
	movementVector.dx = 0;
	movementVector.dy = 0;
	m_airbourne = false;

	collisionPoints.push_back(CollisionPoint(PLAYER_WIDTH/2, 0, HEAD));
	collisionPoints.push_back(CollisionPoint(PLAYER_WIDTH/2, PLAYER_HEIGHT, FEET));
	collisionPoints.push_back(CollisionPoint(0, PLAYER_HEIGHT/3, LEFT));
	collisionPoints.push_back(CollisionPoint(0, (2*PLAYER_HEIGHT)/3, LEFT));
	collisionPoints.push_back(CollisionPoint(PLAYER_WIDTH-1, PLAYER_HEIGHT/3, RIGHT));
	collisionPoints.push_back(CollisionPoint(PLAYER_WIDTH-1, (2*PLAYER_HEIGHT)/3, RIGHT));

	animationMap[PlayerAnimationStep::RUN_RIGHT] = createRunRightAnimation();
	animationMap[PlayerAnimationStep::RUN_LEFT] = createRunLeftAnimation();
	m_currentAnimation = PlayerAnimationStep::RUN_RIGHT;

	m_jumpSound = SoundHelper::loadChunk("resources/sounds/jump.wav");
}

Player::~Player() 
{
	Mix_FreeChunk(m_jumpSound);
}

void Player::resetAnimation()
{
	getAnimation().reset();
}

void Player::draw(Map* map) {
	SDL_Rect bb = getBoundingBox(map);
	Animation& animation = getAnimation();

	SDL_Rect animationRect = animation.getStep();

	TextureStore* store = GameEngine::getInstance().getTextureStore();
	SDL_RenderCopy(GameEngine::getInstance().getRenderer(), store->getOrLoadTexture(player_texture_path), &animationRect, &bb);
}

void Player::handleOuterBounds(Map* map)
{
	MapBounds bounds = map->getOuterBounds();
	if (movementVector.x < bounds.left)
	{
		movementVector.x = bounds.left;
	}
	if (movementVector.x + m_w + 1> bounds.right)
	{
		movementVector.x = bounds.right - m_w - 1;
	}
	if (movementVector.y + m_h > bounds.bottom)
	{
		movementVector.y = bounds.bottom - m_h;
	}
}

void Player::updateAnimation()
{
	if (m_currentAnimation == PlayerAnimationStep::JUMP_RIGHT || m_currentAnimation == PlayerAnimationStep::JUMP_LEFT)
	{
		getAnimation().increaseDelta();
	} 
	else if (movementVector.dx > 0 && m_currentAnimation == PlayerAnimationStep::RUN_RIGHT)
	{
		getAnimation().increaseDelta();
	}
	else if (movementVector.dx < 0 && m_currentAnimation == PlayerAnimationStep::RUN_LEFT)
	{
		getAnimation().increaseDelta();
	}
}

void Player::handle_event(SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_LEFT:
				movementVector.dx -= m_speed;
				m_currentAnimation = PlayerAnimationStep::RUN_LEFT;
				resetAnimation();
				break;
			case SDLK_RIGHT:
				movementVector.dx += m_speed;
				m_currentAnimation = PlayerAnimationStep::RUN_RIGHT;
				resetAnimation();
				break;
			case SDLK_UP:
				if (!m_airbourne)
				{
					movementVector.dy -= 20;	
					m_airbourne = true;
					// Mix_PlayChannel(-1, m_jumpSound, 0);
				}
				break;
		}
	}
	if (event.type == SDL_KEYUP && event.key.repeat == 0)
	{
		switch(event.key.keysym.sym)
		{
			case SDLK_LEFT:
				movementVector.dx += m_speed;
				break;
			case SDLK_RIGHT:
				movementVector.dx -= m_speed;
				break;
		}
	}
}

Animation& Player::getAnimation()
{
	return animationMap[m_currentAnimation];
}

void Player::update(Map* map)
{
	std::vector<Destructable*> destructables = map->getDestructables();
	std::vector<Indestructable*> indestructables = map->getIndestructables();
	Camera* camera = GameEngine::getInstance().getCamera();
	int xBefore = movementVector.x;
	int yBefore = movementVector.y;

	// apply physics
	const int gravity = 1;
	movementVector.dy = std::min(5, movementVector.dy + gravity);
	movementVector.x = movementVector.x + movementVector.dx;
	movementVector.y = movementVector.y + movementVector.dy;
	m_airbourne = true;

	// check for collision
	handleOuterBounds(map);
	handleIndestructableCollisions(indestructables, camera);
	handleDestructableCollisions(destructables, camera);

	updateAnimation();

	MovementVector actualMovement = { movementVector.x, movementVector.y, movementVector.x - xBefore, movementVector.y - yBefore };
	camera->moveCamera(actualMovement, map->getOuterBounds());
}

SDL_Rect Player::getBoundingBox()
{
	SDL_Rect bb = { movementVector.x, movementVector.y, m_w, m_h };
	return bb;
}

SDL_Rect Player::getBoundingBox(Map* map)
{
	MapBounds bounds = map->getOuterBounds();
	Camera* camera = GameEngine::getInstance().getCamera();
	int cameraHalfWidth = camera->getWindowSizeX() / 2;
	int testX = cameraHalfWidth;
	if (bounds.left + cameraHalfWidth > movementVector.x)
	{
		testX = movementVector.x;
	}
	else if (bounds.right - cameraHalfWidth < movementVector.x)
	{
		testX = movementVector.x - (bounds.right - cameraHalfWidth*2);
	}
	SDL_Rect bb = { testX, movementVector.y, m_w, m_h };
	return bb;
}

MovementVector& Player::getMovementVector()
{
	return movementVector;
}

void Player::moveTo(int x, int y)
{
	movementVector.x = x;
	movementVector.y = y;
	movementVector.dx = 0;
	movementVector.dy = 0;
}

void Player::handleIndestructableCollisions(std::vector<Indestructable*> indestructables, Camera* camera)
{
	CollisionDetector detector;
	for(int i = 0; i < indestructables.size(); ++i)
	{
		for(int j = 0; j < collisionPoints.size(); ++j)
		{
			CollisionPoint before = collisionPoints.at(j);
			CollisionPoint translatedPoint(before.x + movementVector.x, before.y + movementVector.y, before.type);
			if (detector.checkCollision(translatedPoint, indestructables.at(i), camera))
			{
				switch (collisionPoints.at(j).type)
				{
					case HEAD:
						movementVector.y = indestructables.at(i)->getBoundingBox().y + indestructables.at(i)->getBoundingBox().h + 1;
						movementVector.dy = 0;
						break;
					case FEET:
						movementVector.y = indestructables.at(i)->getBoundingBox().y - m_h;
						m_airbourne = false;
						break;
					case LEFT:
						movementVector.x = indestructables.at(i)->getBoundingBox().x + indestructables.at(i)->getBoundingBox().w + 1;
						break;
					case RIGHT:
						movementVector.x = indestructables.at(i)->getBoundingBox().x - m_w - 1;
						break;
				}
			}
		}
	}
}

void Player::handleDestructableCollisions(std::vector<Destructable*> destructables, Camera* camera)
{
	CollisionDetector detector;
	for(int i = 0; i < destructables.size(); ++i)
	{
		for(int j = 0; j < collisionPoints.size(); ++j)
		{
			CollisionPoint before = collisionPoints.at(j);
			CollisionPoint translatedPoint(before.x + movementVector.x, before.y + movementVector.y, before.type);
			if (detector.checkCollision(translatedPoint, destructables.at(i), camera))
			{
				switch (collisionPoints.at(j).type)
				{
					case HEAD: 
						movementVector.y = destructables.at(i)->getBoundingBox().y + destructables.at(i)->getBoundingBox().h + 1;
						break;
					case FEET:
						movementVector.y = destructables.at(i)->getBoundingBox().y - m_h;
						m_airbourne = false;
						break;
					case LEFT:
						movementVector.x = destructables.at(i)->getBoundingBox().x + destructables.at(i)->getBoundingBox().w + 1; // + camera->getOffsetX();
						break;
					case RIGHT:
						movementVector.x = destructables.at(i)->getBoundingBox().x - m_w - 1; // + camera->getOffsetX();
						break;
				}
			}
		}
	}
}