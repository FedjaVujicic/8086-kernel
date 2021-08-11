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
				System::lock();
				cout << "In thread id=" << getId() << " i = " << i << endl;
				System::unlock();
#ifndef BCC_BLOCK_IGNORE
				for (int k = 0; k < 10000; ++k)
					for (int j = 0; j < 30000; ++j);
#endif
			}
			System::exitThread();
	}
};


int userMain(int argc, char* argv[])
{
	System::lock();
	MyTestThread *t1 = new MyTestThread(40);
	t1->start();
	cout << "Created thread 1" << endl;

	MyTestThread *t2 = new MyTestThread(20);
	t2->start();
	cout << "Created thread 2" << endl;

	System::unlock();

#ifndef BCC_BLOCK_IGNORE
	for (int i = 0; i < 30; ++i)
	{
		System::lock();
		cout << "main " << i << endl;

		System::unlock();

		for (int j = 0; j < 30000; ++j)
			for (int k = 0; k < 30000; ++k);
	}
#endif
	cout << "Happy End, counter = " << System::counter << endl;

	delete t1; delete t2;

	return 0;
}
