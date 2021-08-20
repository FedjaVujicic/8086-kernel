#ifndef SYSTEM_H_
#define SYSTEM_H_
#include "thread.h"
#include "idle.h"
//#include "semaphor.h"

//extern volatile Idle* idleThread;

class System
{
public:
	static volatile unsigned counter;
	static volatile unsigned contextSwitchRequested;

	static void initialize();
	static void restore();
	static void interrupt timer(...);
};

extern void lock();
extern void unlock();

#endif /* SYSTEM_H_ */
