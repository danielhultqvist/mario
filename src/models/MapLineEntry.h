#ifndef MAP_LINE_ENTRY_H
#define MAP_LINE_ENTRY_H
#include <string>
#include <deque>
#include <gtest/gtest-death-test.h>

class MapLineEntry
{
public:
	std::deque<std::string> extractValues(std::string line);
	
	MapLineEntry(std::string line);
	std::string getType();
	std::deque<std::string> getValues();

private:
	std::string m_type;
	std::deque<std::string> m_values;
	
};

#endif