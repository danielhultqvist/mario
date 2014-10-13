#ifndef MAP_TEST_H
#define MAP_TEST_H

#include <gtest/gtest.h>
#include "../src/models/Map.h"
#include "../src/models/MapLineEntry.h"
#include "../src/models/IndestructableBox.h"

TEST(MapTests, shouldCreateMapContainingIndestructables)
{
	Map testMap;
	testMap.loadFromFile("test/testfiles/testmap_4indestructables.map");
	ASSERT_EQ(testMap.getIndestructables().size(), 4);
}

TEST(MapTests, shouldCreateMapContainingDestructables)
{
	Map testMap;
	testMap.loadFromFile("test/testfiles/testmap_3destructables.map");
	ASSERT_EQ(testMap.getDestructables().size(), 3);
}

TEST(MapTests, shouldLoadIndestructableBoxWithCorrectValues)
{
	std::string testString = "INDESTRUCTABLE_BOX;10;20;30;40;brick.png";
	MapLineEntry entry(testString);
	ASSERT_EQ(entry.getType(), "INDESTRUCTABLE_BOX");
	ASSERT_EQ(entry.getValues().size(), 5);

	IndestructableBox box(entry.getValues());
	ASSERT_EQ(box.getX(), 10);
	ASSERT_EQ(box.getY(), 20);
	ASSERT_EQ(box.getW(), 30);
	ASSERT_EQ(box.getH(), 40);
}

#endif