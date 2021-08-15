/*
 * global.h
 *
 *  Created on: Aug 12, 2021
 *      Author: OS1
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

enum State
{
	BORN,
	READY,
	RUNNING,
	BLOCKED,
	SLEEPING,
	DEAD
};

void lock();

void unlock();


#endif /* GLOBAL_H_ */
