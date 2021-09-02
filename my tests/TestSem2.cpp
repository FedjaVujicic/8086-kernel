/*
 * TestSem.cpp
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

/* Tests semaphore waiting times*/

#include <iostream.h>
#include "system.h"

int t = -1;

extern int syncPrintf(const char *format, ...);

void tick()
{
	++t;
//	syncPrintf("%d\n", t);
}

class TestThread : public Thread
{
public:
	TestThread(Semaphore* s) : Thread(defaultStackSize, defaultTimeSlice)
	{
		sem = s;
		syncPrintf("Created test thread id = %d\n", getId());
	}
	void run()
	{
		sem->wait(0);
		for (int i = 0; i < 40; i++)
		{
			syncPrintf("Running thread id = %d\n", getId());

			for (int j = 0; j < 20000; j++)
				for (int k = 0; k < 20000; k++);
		}
		sem->signal();
	}
	~TestThread()
	{
		waitToComplete();
	}
private:
	Semaphore* sem;
};

class WaitTimeThread : public Thread
{
public:
	WaitTimeThread(Semaphore* s) : Thread(defaultStackSize, defaultTimeSlice)
	{
		sem = s;
		syncPrintf("Created waitTime thread id = %d\n", getId());
	}
	void run()
	{
		sem->wait(50);
		for (int i = 0; i < 40; i++)
		{
			syncPrintf("Running thread id = %d\n", getId());

			for (int j = 0; j < 20000; j++)
				for (int k = 0; k < 20000; k++);
		}
	}
	~WaitTimeThread()
	{
		waitToComplete();
	}
private:
	Semaphore* sem;
};

int userMain(int argc, char** argv)
{
	Semaphore s(1);
	TestThread t1(&s), t2(&s);
	WaitTimeThread w1(&s), w2(&s), w3(&s), w4(&s);

	w1.start();
	w2.start();
	w3.start();
	w4.start();
	t1.start();
	t2.start();

	w1.waitToComplete();
	w2.waitToComplete();
	w3.waitToComplete();
	w4.waitToComplete();
	t1.waitToComplete();
	t2.waitToComplete();


	syncPrintf("Test finished, semaphore value = %d\n", s.val());
	return 0;
}

