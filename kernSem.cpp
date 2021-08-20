/*
 * kernSem.cpp
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

#include "system.h"
#include "kernSem.h"
#include "pcb.h"
#include "queue.h"
#include "SCHEDULE.H"

KernelSem::KernelSem(Semaphore* s, int init)
{
	lock();
	mySem = s;
	value = init;
	pcbWaiting = new Queue;
	unlock();
}

KernelSem::~KernelSem()
{
	lock();
	delete pcbWaiting;
	unlock();
}

int KernelSem::wait(Time maxTimeToWait)
{
	lock();
	if (--value < 0)
	{
		PCB::running->state = BLOCKED;
		pcbWaiting->push((PCB*) PCB::running);
		unlock();
		dispatch();
	}
	else
	{
		unlock();
	}
	return 0;
}

void KernelSem::signal()
{
	lock();
	if (value++ < 0)
	{
		PCB* temp = pcbWaiting->pop();
		temp->state = READY;
		Scheduler::put(temp);
	}
	unlock();
}

int KernelSem::val() const
{
	return value;
}

