#include "MapLineEntry.h"
#include <vector>
#include "../helpers/Logger.h"

const std::string VALUE_DELIMITER = ";";

MapLineEntry::MapLineEntry(std::string line)
{
	m_values = extractValues(line);
	m_type = m_values.at(0);
	m_values.pop_front();
}

std::string MapLineEntry::getType()
{
	return m_type;
}

std::deque<std::string> MapLineEntry::getValues()
{
	return m_values;
}

std::deque<std::string> MapLineEntry::extractValues(std::string line)
{
	std::deque<std::string> result;
	size_t pos = 0;
	while ((pos = line.find(VALUE_DELIMITER)) != std::string::npos)
	{
		result.push_back(line.substr(0, pos));
		line.erase(0, pos + VALUE_DELIMITER.length());
	}
	if (line.length() > 0)
	{
		result.push_back(line);
	}
	return result;
}