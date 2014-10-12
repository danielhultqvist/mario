#ifndef COUNTER_H
#define COUNTER_H

class Counter
{
public:
	Counter(int min, int max, int start);
	int getAndInc();
	
private:
	int internalCounter;
	const int max, min;
};

#endif