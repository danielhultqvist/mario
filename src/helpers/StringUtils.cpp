#include "StringUtils.h"

const std::string StringUtils::WHITESPACE = " \n\r\t";

bool StringUtils::startsWith(std::string fullString, std::string start)
{
	return std::equal(start.begin(), start.end(), fullString.begin());
}

std::string StringUtils::trimLeft(std::string str)
{
	size_t pos = str.find_first_not_of(StringUtils::WHITESPACE);
	return (pos == std::string::npos) ? "" : str.substr(pos);
}

std::string StringUtils::trimRight(std::string str)
{
	size_t pos = str.find_last_not_of(StringUtils::WHITESPACE);
	return (pos == std::string::npos) ? "" : str.substr(0, pos+1);
}

std::string StringUtils::trim(std::string str)
{
	return trimRight(trimLeft(str));
}