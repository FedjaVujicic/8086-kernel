#include <iostream.h>
#include "system.h"
#include "thread.h"

void tick(){}

class MyTestThread : public Thread
{
public:

	MyTestThread(Time timeSlice = defaultTimeSlice, StackSize stackSize = defaultStackSize) : Thread(timeSlice, stackSize)
	{}

	void run()
	{
		for (int i = 0; i < 30; ++i)
			{
				lock();
				cout << "In thread id=" << getId() << " i = " << i << endl;
//				cout << "In other thread id= " << (getThreadById(3 - getId()))->getId() << " State = " << (getThreadById(3 - getId()))->getState() << endl;
				unlock();
#ifndef BCC_BLOCK_IGNORE
				for (int k = 0; k < 10000; ++k)
					for (int j = 0; j < 30000; ++j);
#endif
			}
	}

	~MyTestThread()
	{
		waitToComplete();
	}
};


int userMain(int argc, char* argv[])
{
	lock();
	MyTestThread *t1 = new MyTestThread(20);
	t1->start();

	MyTestThread *t2 = new MyTestThread(20);
	t2->start();

	unlock();
/*
#ifndef BCC_BLOCK_IGNORE
	for (int i = 0; i < 30; ++i)
	{
		lock();
		cout << "main " << i << endl;

		unlock();

		for (int j = 0; j < 30000; ++j)
			for (int k = 0; k < 30000; ++k);
	}
#endif
	cout << "Happy End, counter = " << System::counter << endl;
*/

	delete t1;
	delete t2;

	return 0;
}
