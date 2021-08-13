#ifndef PCB_H_
#define PCB_H_
#include "thread.h"
#include "global.h"

class Queue;

class PCB
{
private:
	friend class System;
	friend class Thread;
	friend class Queue;

	static volatile ID curID;
	ID id;

	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned timeSlice;
	unsigned stackSize;
	unsigned* stack;
	Thread *myThread;
	static volatile PCB* running;
	State state;

	static Queue* pcbList;

	void initializeStack();
	static void wrapper();

	PCB (Thread *myThread = 0, Time timeSlice = defaultTimeSlice, StackSize stackSize = defaultStackSize); //delete default values

	~PCB();
};




#endif /* PCB_H_ */
