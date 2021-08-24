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

extern Queue sleepList;

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
		if (maxTimeToWait != 0)
		{
			PCB::running->timeToWait = maxTimeToWait;
			sleepList.push((PCB*) PCB::running);
		}
		PCB::running->state = BLOCKED;
		PCB::running->mySem = this;
		pcbWaiting->push((PCB*) PCB::running);
		unlock();
		dispatch();
		lock();
		if (maxTimeToWait == 0) //non-sleeping threads
		{
			//signalled
			unlock();
			return 1;
		}
		else //sleeping threads
		{
			if (PCB::running->timeToWait != 0)
			{
				//signalled, remove from sleepList
				PCB::running->timeToWait = 0;
				sleepList.remove((PCB*) PCB::running);
				unlock();
				return 1;
			}
			else
			{
				//time limit exceeded, remove from sleeplist
				sleepList.remove((PCB*) PCB::running);
				unlock();
				return 2;
			}
		}
	}

	unlock();
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

