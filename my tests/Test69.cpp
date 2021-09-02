#include <iostream.h>
#include "system.h"

void tick(){}

class MyTestThread : public Thread
{
public:

	MyTestThread(StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice) : Thread(stackSize, timeSlice)
	{
		cout << "Created thread id = " << getId() << endl;
	}

	void run()
	{
		for (int i = 0; i < 30; ++i)
			{
				lock();
				cout << "In thread id=" << getId() << " i = " << i << endl;
				unlock();
#ifndef BCC_BLOCK_IGNORE
				for (int k = 0; k < 10000; ++k)
					for (int j = 0; j < 30000; ++j);
#endif
			}
		cout << "Finished thread id=" << getId() << endl;
	}

	~MyTestThread()
	{
		waitToComplete();
		cout << "Deleted thread id=" << getId() << endl;
	}
};


int userMain(int argc, char* argv[])
{
	lock();
	MyTestThread *t1 = new MyTestThread(4096, 20);
	t1->start();

	MyTestThread *t2 = new MyTestThread(4096, 20);
	t2->start();

	unlock();

	delete t1;
	delete t2;

	return 0;
}

