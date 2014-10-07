#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

#include <gtest/gtest.h>
#include "../src/models/Player.h"
#include "../src/models/MovementVector.h"

/**
 * Simulates a SDL_Event
 * @key Key to be pressed down
 */
inline SDL_Event simulateKeyEvent(int key, int type)
{
	SDL_Event event;
	event.type = type;
	event.key.keysym.sym = key;
	event.key.repeat = 0;
	return event;
}

inline Indestructable* createIndestructable(std::string x, std::string y, std::string w, std::string h)
{
	std::deque<std::string> values;
	values.push_back(x);
	values.push_back(y);
	values.push_back(w);
	values.push_back(h);
	values.push_back("");
	return  new IndestructableBox(values);
}

TEST(PlayerTest, shouldNotBeAbleToDoubleJump)
{
	// Given player with zero movement vector 
	Player testPlayer(1,1);
	int beforeJumps = testPlayer.getMovementVector().dy;

	// When jump button is pressed twice 
	SDL_Event event = simulateKeyEvent(SDLK_SPACE, SDL_KEYDOWN);
	testPlayer.handle_event(event);
	int afterFirstJump = testPlayer.getMovementVector().dy;
	testPlayer.handle_event(event);
	int afterSecondJump = testPlayer.getMovementVector().dy;

	// Then only one jump event should be used
	ASSERT_NE(afterFirstJump, beforeJumps);
	ASSERT_EQ(afterSecondJump, afterFirstJump);
}

TEST(PlayerTest, shouldNotFallThroughBox)
{
	//ASSERT_EQ(true ,false);
}

TEST(PlayerTest, shouldNotFallThroughIndestructable)
{
	// Given map with indestructable object and player
	Map map;
	Indestructable* indestructable = createIndestructable("100", "100", "20", "20");
	map.getIndestructables().push_back(indestructable);
	Player player(100, 55);
	player.moveTo(100, 100 - player.getBoundingBox().h - 1);

	// When player jumps
	player.getMovementVector().dy = 10;
	player.update(&map);

	// Then player should not move through it
	ASSERT_EQ(indestructable->getBoundingBox().y, player.getBoundingBox().y+player.getBoundingBox().h);
}

TEST(PlayerTest, shouldNotJumpThroughIndestructable)
{
	// Given map with indestructable object and player
	Map map;
	Indestructable* indestructable = createIndestructable("100", "100", "20", "20");
	map.getIndestructables().push_back(indestructable);
	Player player(100,125);
	player.moveTo(100, 100 + indestructable->getBoundingBox().h + 1);

	// When player jumps
	player.getMovementVector().dy = -3;
	player.update(&map);

	// Then player should not move through it
	ASSERT_EQ(0, player.getMovementVector().dy);
	ASSERT_EQ(indestructable->getBoundingBox().y+indestructable->getBoundingBox().h+1, player.getBoundingBox().y);
}

TEST(PlayerTest, shouldNotPassThroughIndestructableToTheRight)
{
	// Given map with indestructable object and player
	Map map;
	Indestructable* indestructable = createIndestructable("100", "100", "20", "20");
	map.getIndestructables().push_back(indestructable);
	Player player(72,100);

	// When player goes to the right
	player.getMovementVector().dx = 3;
	player.update(&map);

	// Then player should not move through it
	ASSERT_EQ(player.getBoundingBox().x+player.getBoundingBox().w + 1, indestructable->getBoundingBox().x);
}

TEST(PlayerTest, shouldNotPassThroughIndestructableToTheLeft)
{
	// Given map with indestructable object and player
	Map map;
	Indestructable* indestructable = createIndestructable("100", "100", "20", "20");
	map.getIndestructables().push_back(indestructable);
	Player player(128,100);

	// When player goes to the right
	player.getMovementVector().dx = -3;
	player.update(&map);

	// Then player should not move through it
	ASSERT_EQ(player.getBoundingBox().x, indestructable->getBoundingBox().x+indestructable->getBoundingBox().w+1);
}

#endif