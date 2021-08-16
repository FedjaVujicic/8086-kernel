/*
 * TestWait.cpp
 *
 *  Created on: Aug 16, 2021
 *      Author: OS1
 */
#include <iostream.h>
#include "system.h"

void tick() {}


class TestThread : public Thread
{
public:
	TestThread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice) : Thread(stackSize, timeSlice)
	{
		cout << "Created test thread " << getId() << endl;
	}

	~TestThread()
	{
		waitToComplete();
		cout << "Deleted test thread " << getId() << endl;
	}

	void run()
	{
		for (int i = 0; i < 21; i++)
		{
			cout << "In thread " << getId() << " i = " << i << endl;
			for (int k = 0; k < 30000; k++)
				for (int j = 0; j < 30000; j++);
		}
	}

};

class WaitingThread : public Thread
{
public:
	WaitingThread(TestThread* myThread, StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice) : Thread(stackSize, timeSlice)
	{
		this->myThread = myThread;
		cout << "Created waiting thread " << getId() << endl;
	}

	~WaitingThread()
	{
		waitToComplete();
		cout << "Deleted waiting thread " << getId() << endl;
	}

	void run()
	{
		myThread->waitToComplete();
	}

private:
	TestThread* myThread;
};

int userMain(int argc, char** argv)
{
	TestThread t1, t2;
	WaitingThread w1(&t1), w2(&t2), w3(&t1);
	t1.start(); t2.start(); w1.start(); w2.start(); w3.start();
	return 0;
}

