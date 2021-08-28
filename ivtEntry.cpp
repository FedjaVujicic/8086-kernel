/*
 * ivtEntry.cpp
 *
 *  Created on: Aug 28, 2021
 *      Author: OS1
 */

#include "ivtEntry.h"
#include "kernEv.h"
#include <dos.h>

IvtEntry* IvtEntry::ivtEntries[NUM_ENTRIES];

#ifndef BCC_BLOCK_IGNORE
IvtEntry::IvtEntry(IVTNo numEntry, pInterrupt newRoutine)
{
	lock();
	this->numEntry = numEntry;
	oldRoutine = getvect(numEntry);
	setvect(numEntry, newRoutine);
	ivtEntries[numEntry] = this;
	unlock();
}
#endif

IvtEntry::~IvtEntry()
{
#ifndef BCC_BLOCK_IGNORE
	setvect(numEntry, oldRoutine);
#endif
}

void IvtEntry::callOldRoutine()
{
	oldRoutine();
}

void IvtEntry::signal()
{
	myEvent->signal();
}
