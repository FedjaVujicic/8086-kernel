#include "PCB.h"
#include "system.h"
#include <dos.h>
#include "SCHEDULE.H"

ID PCB::curID = 0;

void PCB::wrapper()
{
	running->myThread->run();
	System::lock();
	running->finished = 1;
	System::unlock();
	System::dispatch();
}

PCB::PCB (Thread *myThread, Time timeSlice, StackSize stackSize)
{
	this->stackSize = stackSize;
	this->timeSlice = timeSlice;
	this->myThread = myThread;
	this->finished = 0;
	id = curID++;
	initializeStack();
}

volatile PCB* PCB::running = 0;

void PCB::initializeStack()
{
	System::lock();
	stack = new unsigned[stackSize];
	stack[stackSize - 1] = 0x200;
#ifndef BCC_BLOCK_IGNORE
	stack[stackSize - 2] = FP_SEG(wrapper);
	stack[stackSize - 3] = FP_OFF(wrapper);

	sp = FP_OFF(stack + stackSize - 12);
	ss = FP_SEG(stack + stackSize - 12);
	bp = FP_OFF(stack + stackSize - 12);
#endif
	finished = 0;
	System::unlock();
}

PCB::~PCB()
{
	System::lock();
	if (stack != 0)
	{
		delete stack;
	}
	System::unlock();
}
