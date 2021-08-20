#include "thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "system.h"
#include "queue.h"
//#include "idle.h"

//extern Idle* idleThread;

extern Queue pcbList;

void dispatch()
{
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif

	System::contextSwitchRequested = 1;
	System::timer();

#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}

Thread::Thread (StackSize stackSize, Time timeSlice)
{
	lock();
	myPCB = new PCB(this, stackSize, timeSlice);
	unlock();
}


Thread::~Thread()
{
	lock();
	delete myPCB;
	unlock();
}

void Thread::start()
{
	lock();
	myPCB->state = READY;
	Scheduler::put(myPCB);
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
	if (id > pcbList.getSize())
	{
		return 0;
	}
	return (pcbList.find(id))->myThread;
}

void Thread::waitToComplete()
{
	lock();
	if (myPCB != PCB::running && myPCB->state != BORN && myPCB->state != DEAD)
	{
		PCB::running->state = BLOCKED;
		myPCB->pcbWaiting->push((PCB*) PCB::running);
		unlock();
		dispatch();
	}
	else
	{
		unlock();
	}
}
