#ifndef SYSTEM_H_
#define SYSTEM_H_
#include "thread.h"



class System
{
public:
	static volatile unsigned counter;
	static volatile unsigned contextSwitchRequested;

	static void initialize();
	static void restore();
	static void interrupt timer(...);
};

#endif /* SYSTEM_H_ */
