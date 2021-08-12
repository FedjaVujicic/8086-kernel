#include "thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "system.h"

#include <iostream.h> // delet dis

Thread::Thread (Time timeSlice, StackSize stackSize)
{
	System::lock();
	myPCB = new PCB(this, timeSlice, stackSize);
	cout << "Created thread id=" << getId() << " State=" << getState() << endl; // delet
	System::unlock();
}


Thread::~Thread()
{
	System::lock();
	cout << "Deleted thread id=" << getId() << " State="<< getState() << endl; // delet
	System::lock(); // delet
	delete myPCB;
	System::unlock();
}

void Thread::start()
{
	System::lock();
	myPCB->state = READY;
	Scheduler::put(myPCB);
	cout << "Thread in scheduler, state=" << getState() << endl;// delet
	System::unlock();
}

ID Thread::getId()
{
	return myPCB->id;
}

State Thread::getState()
{
	return myPCB->state;
}
