#include "PCB.h"
#include "system.h"
#include <dos.h>
#include "SCHEDULE.H"

ID PCB::curID = 0;

void PCB::wrapper()
{
	running->myThread->run();
	lock();
	running->state = DEAD;
	unlock();
	System::dispatch();
}

PCB::PCB (Thread *myThread, Time timeSlice, StackSize stackSize)
{
	lock();
	this->stackSize = stackSize;
	this->timeSlice = timeSlice;
	this->myThread = myThread;
	id = curID++;
	state = BORN;
	initializeStack();
	unlock();
}

volatile PCB* PCB::running = 0;

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

PCB::~PCB()
{
	lock();
	if (stack != 0)
	{
		delete stack;
	}
	unlock();
}
