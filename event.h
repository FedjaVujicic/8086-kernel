/*
 * event.h
 *
 *  Created on: Aug 28, 2021
 *      Author: OS1
 */

#ifndef EVENT_H_
#define EVENT_H_

#include "ivtEntry.h"

#define PREPAREENTRY(numEntry, callOld)\
void interrupt inter##numEntry(...);\
IvtEntry newEntry##numEntry(numEntry, inter##numEntry);\
void interrupt inter##numEntry(...)\
{\
	newEntry##numEntry.signal();\
	if (callOld == 1)\
	{\
		newEntry##numEntry.callOldRoutine();\
	}\
}


typedef unsigned char IVTNo;

class KernelEv;

class Event
{
public:
	Event (IVTNo ivtNo);
	~Event ();

	void wait ();
protected:
	friend class KernelEv;

	void signal(); // can call KernelEv
private:
	KernelEv* myImpl;
};



#endif /* EVENT_H_ */
