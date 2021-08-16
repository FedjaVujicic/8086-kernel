#include "PCB.h"
#include "system.h"
#include <dos.h>
#include "SCHEDULE.H"
#include "queue.h"
#include "global.h"
#include "thread.h"

volatile ID PCB::curID = 0;
volatile PCB* PCB::running = 0;
Queue* pcbList = 0;

void PCB::wrapper()
{
	running->myThread->run();
	lock();
	running->state = DEAD;
	PCB* temp;
	while (running->pcbWaiting->getSize() > 0)
	{
		temp = running->pcbWaiting->pop();
		temp->state = READY;
		Scheduler::put(temp);
	}
	unlock();
	dispatch();
}

PCB::~PCB()
{
	lock();
	if (stack != 0)
	{
		delete stack;
	}
	unlock();
}

PCB::PCB (Thread *myThread, StackSize stackSize, Time timeSlice)
{
	lock();
	this->stackSize = stackSize;
	this->timeSlice = timeSlice;
	this->myThread = myThread;
	id = curID++;
	state = BORN;
	initializeStack();
	pcbList->push(this);
	pcbWaiting = new Queue();
	unlock();
}

void PCB::initializeStack()
{
	lock();
	stack = new unsigned[stackSize];
	stack[stackSize - 1] = 0x200;
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize - 2] = FP_SEG(wrapper);
	stack[stackSize - 3] = FP_OFF(wrapper);

	sp = FP_OFF(stack + stackSize - 12);
	ss = FP_SEG(stack + stackSize - 12);
	bp = FP_OFF(stack + stackSize - 12);
#endif
	unlock();
}
