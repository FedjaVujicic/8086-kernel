/*
 * TestAsd.cpp
 *
 *  Created on: Sep 2, 2021
 *      Author: OS1
 */

#include "system.h"

//Tests semaphore values

extern int syncPrintf(const char *format, ...);

void tick()
{}

Semaphore sleepSem(0);
Semaphore multiplex(5);

class TestThread : public Thread
{
public:
	void run()
	{
		sleepSem.wait(10);
		sleepSem.wait(10);
		multiplex.wait(0);
		for (int i = 0; i < 5; i++)
		{
			syncPrintf("Running thread id=%d, i=%d\n", getId(), i);
			sleepSem.wait(30);
		}
		multiplex.signal();
	}

	~TestThread()
	{
		waitToComplete();
	}
};

int userMain(int argc, char** argv)
{
	TestThread t1,t2,t3,t4,t5,t6,t7,t8,t9,t10;
	t1.start();t2.start();t3.start();t4.start();t5.start();t6.start();t7.start();t8.start();t9.start();t10.start();

	t1.waitToComplete();t2.waitToComplete();t3.waitToComplete();t4.waitToComplete();t5.waitToComplete();t6.waitToComplete();t7.waitToComplete();t8.waitToComplete();t9.waitToComplete();t10.waitToComplete();

	syncPrintf("Multiplex value = %d\n", multiplex.val());
	syncPrintf("Sleep sem value = %d\n", sleepSem.val());
	syncPrintf("\n");
	syncPrintf("Test finished!\n");
	return 0;
}


