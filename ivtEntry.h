/*
 * ivtEntry.h
 *
 *  Created on: Aug 28, 2021
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_

#include "system.h"

typedef unsigned char IVTNo;

const int NUM_ENTRIES = 256;

class KernelEv;

class IvtEntry
{
public:
	IvtEntry(IVTNo numEntry, pInterrupt newRoutine);
	~IvtEntry();

	void callOldRoutine();

	void signal();

private:
	friend class KernelEv;

	IVTNo numEntry;
	pInterrupt oldRoutine;

	KernelEv* myEvent;

	static IvtEntry* ivtEntries[NUM_ENTRIES];
};



#endif /* IVTENTRY_H_ */
