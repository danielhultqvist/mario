#ifndef STRING_UTILS_H
#define STRING_UTILS_H
#include <string>

class StringUtils
{
public:
	static std::string const WHITESPACE;
	static bool startsWith(std::string fullString, std::string start);
	static std::string trimLeft(std::string str);
	static std::string trimRight(std::string str);
	static std::string trim(std::string);

};

#endif