#include "Counter.h"

Counter::Counter(int min, int max, int start) : max(max), min(min)
{
	internalCounter = start;
}

int Counter::getAndInc()
{
	int retVal = internalCounter++;
	if (internalCounter > max)
	{
		internalCounter = min;
	}
	return retVal;
}