#include "PCB.h"
#include "system.h"
#include <dos.h>
#include "SCHEDULE.H"
#include "queue.h"
#include "thread.h"

volatile ID PCB::curID = -1;
volatile PCB* PCB::running = 0;

extern Queue pcbList;

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
	if (pcbWaiting != 0)
	{
		delete pcbWaiting;
	}
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
	timeToWait = 0;
	mySem = 0;
	id = curID++;
	state = BORN;
	initializeStack();
	pcbList.push(this);
	pcbWaiting = new Queue();
	unlock();
}

void PCB::initializeStack()
{

	lock();
	stackSize /= sizeof(unsigned);
	stack = new unsigned[stackSize];
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize - 5] = 0x200;
	stack[stackSize - 6] = FP_SEG(wrapper);
	stack[stackSize - 7] = FP_OFF(wrapper);

	ss = FP_SEG(stack + stackSize - 16);
	sp = FP_OFF(stack + stackSize - 16);
	bp = sp;
#endif
	unlock();
}
