/*
 * TestQwe.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: OS1
 */

#include "system.h"
#include "kernEv.h"
#include "event.h"

extern int syncPrintf(const char *format, ...);

void tick(){}

class TestThread : public Thread
{
public:
	void run()
	{
		Event e(9);
		syncPrintf("Waiting for event\n");
		e.wait();
		syncPrintf("Event occured\n");
	}
	~TestThread()
	{
		waitToComplete();
	}
};

PREPAREENTRY(9, 0)

int userMain(int argc, char** argv)
{
	syncPrintf("Test started\n");
	TestThread t;
	t.start();

	t.waitToComplete();

	syncPrintf("Test finished\n");
	return 0;
}


