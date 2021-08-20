/*
 * semaphor.cpp
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

#include "system.h"
#include "kernSem.h"

Semaphore::Semaphore(int init)
{
	lock();
	myImpl = new KernelSem(this, init);
	unlock();
}

Semaphore::~Semaphore()
{
	lock();
	delete myImpl;
	unlock();
}

int Semaphore::wait(Time maxTimeToWait)
{
	return myImpl->wait(maxTimeToWait);
}

void Semaphore::signal()
{
	myImpl->signal();
}

int Semaphore::val() const
{
	return myImpl->val();
}

