/*
 * idle.cpp
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */

#include "idle.h"

Idle::Idle():Thread(4096, 1){}

void Idle::run()
{
	while(1);
}

