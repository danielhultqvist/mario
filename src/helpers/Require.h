#ifndef REQUIRE_H
#define REQUIRE_H

class Require
{
public:
	template<typename T>
	static bool equal(T a, T b)
	{
		return a == b;
	}
};

#endif