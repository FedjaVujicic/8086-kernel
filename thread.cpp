#include "thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "system.h"
#include "queue.h"

#include <iostream.h> // delet dis

Thread::Thread (Time timeSlice, StackSize stackSize)
{
	lock();
	myPCB = new PCB(this, timeSlice, stackSize);
	cout << "Created thread id=" << getId() << " State=" << getState() << endl; // delet
	unlock();
}


Thread::~Thread()
{
	lock();
	cout << "Deleted thread id=" << getId() << " State="<< getState() << endl; // delet
	lock(); // delet
	delete myPCB;
	unlock();
}

void Thread::start()
{
	lock();
	myPCB->state = READY;
	Scheduler::put(myPCB);
	cout << "Thread in scheduler, state=" << getState() << endl;// delet
	unlock();
}

ID Thread::getId()
{
	return myPCB->id;
}

State Thread::getState()
{
	return myPCB->state;
}

Thread * Thread::getThreadById(ID id)
{
	return (PCB::pcbList->find(id))->myThread;
}
