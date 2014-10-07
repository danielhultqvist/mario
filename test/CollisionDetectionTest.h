#ifndef COLLISION_TEST_H
#define COLLISION_TEST_H

#include <gtest/gtest.h>
#include "../src/models/Indestructable.h"
#include "../src/models/IndestructableBox.h"
#include "../src/models/Player.h"
#include "../src/engine/CollisionDetector.h"

inline IndestructableBox* createTestBox(std::string x, std::string y, std::string w, std::string h)
{
	std::deque<std::string> values;
	values.push_back(x);
	values.push_back(y);
	values.push_back(w);
	values.push_back(h);
	values.push_back("image.png");
	return new IndestructableBox(values);
}

TEST(CollisionTest, shouldNotGivePositiveDetection)
{
	IndestructableBox* myBox = createTestBox("10", "10", "30", "30");
	Player* player = new Player(100, 100);
	CollisionDetector detector;
	bool collision = detector.checkCollision(myBox, player);
	delete myBox;
	delete player;
	ASSERT_FALSE(collision);
}

TEST(CollisionTest, shouldDetectCollisionBetweenPlayerAndBoxToRight)
{
	// note that player is 20 pixels wide and 40pixels tall
	IndestructableBox* myBox = createTestBox("100", "100", "30", "30");
	Player* player = new Player(90, 100);
	CollisionDetector detector;
	bool collision = detector.checkCollision(myBox, player);
	delete myBox;
	delete player;
	ASSERT_TRUE(collision);
}

#endif