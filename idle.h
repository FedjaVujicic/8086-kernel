/*
 * idle.h
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_

#include "thread.h"

class Idle : public Thread
{
public:
	Idle();
	void run();
};




#endif /* IDLE_H_ */
