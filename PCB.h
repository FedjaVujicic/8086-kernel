#ifndef PCB_H_
#define PCB_H_
#include "thread.h"
#include "queue.h"

enum State
{
	BORN,
	READY,
	RUNNING,
	BLOCKED,
	SLEEPING,
	DEAD
};

class PCB
{
private:
	friend class System;
	friend class Thread;
	friend class Queue;
	friend class KernelSem;

	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned timeSlice;
	unsigned stackSize;
	unsigned* stack;
	Thread *myThread;
	static volatile PCB* running;
	State state;

	static volatile ID curID;
	ID id;

	Queue* pcbWaiting;

	void initializeStack();
	static void wrapper();

	PCB (Thread *myThread = 0, StackSize stackSize = defaultStackSize, Time timeSlice = defaultTimeSlice); //delete default values

	~PCB();
};



#endif /* PCB_H_ */
