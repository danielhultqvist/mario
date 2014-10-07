#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <string>

class TestRunner
{
public:
	int runAllTests();
	int runTestGroup(std::string group);
	int runSingleTest(std::string group, std::string testname);
};

#endif