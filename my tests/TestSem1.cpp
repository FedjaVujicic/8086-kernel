/*
 * TestSem.cpp
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

/* Tests semaphore functions with a lot of semaphores and without maximum waiting time*/

#include <iostream.h>
#include "system.h"

void tick() {}

extern int syncPrintf(const char *format, ...);

class TestThread : public Thread
{
public:
	TestThread(Semaphore* s) : Thread(defaultStackSize, defaultTimeSlice)
	{
		sem = s;
	}
	void run()
	{
		sem->wait(0);
		for (int i = 0; i < 10; i++)
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

int userMain(int argc, char** argv)
{
	Semaphore s(3);
	TestThread t1(&s), t2(&s), t3(&s), t4(&s), t5(&s), t6(&s), t7(&s), t8(&s), t9(&s), t10(&s), t11(&s), t12(&s), t13(&s), t14(&s), t15(&s), t16(&s), t17(&s), t18(&s);

	t1.start();
	t2.start();
	t3.start();
	t4.start();
	t5.start();
	t6.start();
	t7.start();
	t8.start();
	t9.start();
	t10.start();
	t11.start();
	t12.start();
	t13.start();
	t14.start();
	t15.start();
	t16.start();
	t17.start();
	t18.start();



	return 0;
}

