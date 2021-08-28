/*
 * kernEv.h
 *
 *  Created on: Aug 28, 2021
 *      Author: OS1
 */

#ifndef KERNEV_H_
#define KERNEV_H_

#include "event.h"

class PCB;

class KernelEv
{
public:
	KernelEv (IVTNo ivtNo);

	void wait ();
protected:
	friend class Event;

	void signal();
private:
	friend class IvtEntry;

	PCB* myPCB;
};




#endif /* KERNEV_H_ */
