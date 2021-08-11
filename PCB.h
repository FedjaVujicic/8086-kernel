#ifndef PCB_H_
#define PCB_H_
#include "thread.h"

class PCB
{
private:
	friend class System;
	friend class Thread;

	static ID curID;
	ID id;

	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned finished;
	unsigned timeSlice;
	unsigned stackSize;
	unsigned* stack;
	Thread *myThread;
	static volatile PCB* running;

	void initializeStack();
	static void wrapper();

	PCB (Thread *myThread = 0, Time timeSlice = defaultTimeSlice, StackSize stackSize = defaultStackSize); //delete default values

	~PCB();
};




#endif /* PCB_H_ */
