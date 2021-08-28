/*
 * event.cpp
 *
 *  Created on: Aug 28, 2021
 *      Author: OS1
 */

#include "kernEv.h"

Event::Event(IVTNo ivtNo)
{
	myImpl = new KernelEv(ivtNo);
}

Event::~Event()
{
	delete myImpl;
}

void Event::wait()
{
	myImpl->wait();
}

void Event::signal()
{
	myImpl->signal();
}
