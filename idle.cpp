/*
 * idle.cpp
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

#include "idle.h"

#include <iostream.h>

Idle::Idle():Thread(4096, 1){}

void Idle::run()
{
	while(1);
}

//To avoid putting the idle thread into the scheduler
void Idle::start()
{}

