#include <iostream.h>
#include "system.h"
#include "thread.h"

class A : public Thread
{
public:

	A(Time timeSlice = defaultTimeSlice, StackSize stackSize = defaultStackSize) : Thread(timeSlice, stackSize)
	{}

	void run()
	{
		for (int i = 0; i < 30; ++i)
			{
				System::lock();
				cout << "In a() i = " << i << endl;
				System::unlock();
#ifndef BCC_BLOCK_IGNORE
				for (int k = 0; k < 10000; ++k)
					for (int j = 0; j < 30000; ++j);
#endif
			}
			System::exitThread();
	}
};

class B: public Thread
{
public:
	B(Time timeSlice = defaultTimeSlice, StackSize stackSize = defaultStackSize) : Thread(timeSlice, stackSize)
	{}

	void run()
	{
		for (int i = 0; i < 30; ++i)
			{
				System::lock();
				cout << "In b() i = " << i << endl;
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
	A *t1 = new A(40);
	t1->start();
	cout << "Created a" << endl;

	B *t2 = new B(20);
	t2->start();
	cout << "Created b" << endl;

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
