#include <iostream>
#include <stdio.h>
#include <tchar.h>
#include <gtest/gtest.h>
#include "TestRunner.h"

// INCLUDE ALL TESTS HERE
#include "MapTest.h"
#include "CollisionDetectionTest.h"
#include "PlayerTest.h"

int empty_argc = 0;
const char* empty_args[1] = {""};

int TestRunner::runAllTests()
{
	::testing::InitGoogleTest(&empty_argc, (char**)empty_args);
	return RUN_ALL_TESTS();	
}

int TestRunner::runTestGroup(std::string group)
{
	::testing::GTEST_FLAG(filter) = group + ".*";
	::testing::InitGoogleTest(&empty_argc, (char**)empty_args);
	return RUN_ALL_TESTS();	
}

int TestRunner::runSingleTest(std::string group, std::string testname)
{
	::testing::GTEST_FLAG(filter) = group + "." + testname;
	::testing::InitGoogleTest(&empty_argc, (char**)empty_args);
	return RUN_ALL_TESTS();	
}