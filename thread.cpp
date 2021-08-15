#include "thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "system.h"
#include "queue.h"
#include "global.h"

#include <iostream.h> // delet dis

extern Queue* pcbList;

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
	cout << "Thread id=" << getId() <<" in scheduler, state=" << getState() << endl;// delet
	unlock();
}

ID Thread::getId()
{
	return myPCB->id;
}

ID Thread::getRunningId()
{
	return PCB::running->id;
}


Thread* Thread::getThreadById(ID id)
{
	return (pcbList->find(id))->myThread;
}

State Thread::getState()
{
	return myPCB->state;
}

void Thread::waitToComplete()
{
	lock();
	if (myPCB != PCB::running && myPCB->state != BORN && myPCB->state != DEAD)
	{
		PCB::running->state = BLOCKED;
		myPCB->pcbWaiting->push((PCB*) PCB::running);
		unlock();
		System::dispatch();
	}
	else
	{
		unlock();
	}
}
