#include "thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "system.h"

Thread::Thread (Time timeSlice, StackSize stackSize)
{
	System::lock();
	myPCB = new PCB(this, timeSlice, stackSize);
	System::unlock();
}


Thread::~Thread()
{
	System::lock();
	delete myPCB;
	System::unlock();
}

void Thread::start()
{
	System::lock();
	Scheduler::put(myPCB);
	System::unlock();
}


void Thread::waitToComplete()
{

}
