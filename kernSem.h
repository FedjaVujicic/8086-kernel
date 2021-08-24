/*
 * kernSem.h
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

#ifndef KERNSEM_H_
#define KERNSEM_H_

#include "semaphor.h"

class Queue;

class KernelSem
{
public:
	KernelSem(Semaphore* s, int init = 1);

	~KernelSem();

	int wait(Time maxTimeToWait);
	void signal();

	int val() const;
private:
	friend class Queue;

	volatile int value;
	Semaphore* mySem;
	Queue* pcbWaiting;
};



#endif /* KERNSEM_H_ */
