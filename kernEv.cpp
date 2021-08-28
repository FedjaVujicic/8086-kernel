/*
 * kernEv.cpp
 *
 *  Created on: Aug 28, 2021
 *      Author: OS1
 */

#include "kernEv.h"
#include "system.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "ivtEntry.h"

KernelEv::KernelEv(IVTNo ivtNo)
{
	lock();
	myPCB = (PCB*) PCB::running;
	IvtEntry::ivtEntries[ivtNo]->myEvent = this;
	unlock();
}


void KernelEv::wait()
{
	lock();
	if (PCB::running != myPCB)
	{
		unlock();
		return;
	}
	PCB::running->state = BLOCKED;
	unlock();
	dispatch();
}

void KernelEv::signal()
{
	lock();
	myPCB->state = READY;
	Scheduler::put(myPCB);
	unlock();
}

