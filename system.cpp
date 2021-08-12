#include <iostream.h>
#include <dos.h>
#include "SCHEDULE.H"
#include "system.h"
#include "PCB.h"
#include "thread.h"


volatile unsigned tsp, tss, tbp;
volatile unsigned System::counter = 20;
volatile unsigned System::contextSwitchRequested = 0;

typedef void interrupt (*pInterrupt)(...); // for setvect and getvect
pInterrupt oldRoutine = 0;

extern void tick();

void System::lock()
{
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
}

void System::unlock()
{
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}

void interrupt System::timer(...){

	if (!contextSwitchRequested)
	{
		tick();
		System::counter--;
#ifndef BCC_BLOCK_IGNORE
		asm int 60h;
#endif
	}

	if (System::counter == 0 || contextSwitchRequested)
	{
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
#endif

		PCB::running->sp = tsp;
		PCB::running->ss = tss;
		PCB::running->bp = tbp;

		cout << "Context switch! Counter= " << counter << endl;
		System::lock();

		if (PCB::running->state == RUNNING)
		{
			PCB::running->state = READY;
			Scheduler::put((PCB*) PCB::running);
		}
		else // delet
		{
			cout << "Thread dead, not putting into the scheduler." << endl;
			System::lock();
		}
		PCB::running = Scheduler::get();
		if (PCB::running != 0)
		{
			PCB::running->state = RUNNING;
		}

		tsp = PCB::running->sp;
		tss = PCB::running->ss;
		tbp = PCB::running->bp;

		System::counter = PCB::running->timeSlice;

#ifndef BCC_BLOCK_IGNORE
		asm {
			mov sp, tsp
			mov ss, tss
			mov bp, tbp
		}
#endif
	} 
		                                              
	System::contextSwitchRequested = 0;
}

//Context switch on request
void System::dispatch()
{
	System::lock();

	System::contextSwitchRequested = 1;
	System::timer();

	System::unlock();
}

//Saves old timer routine to 60h, and puts the user timer routine to 8h
void System::initialize()
{
	System::lock();
	PCB::running = new PCB(0, 10);
	PCB::running->state = RUNNING;
#ifndef BCC_BLOCK_IGNORE
	oldRoutine = getvect(0x08);
	setvect(0x60, oldRoutine);
	setvect(0x08, timer);
#endif
	System::unlock();
}

//Restores the old timer routine
void System::restore()
{
	System::lock();
#ifndef BCC_BLOCK_IGNORE
	setvect(0x08, oldRoutine);
#endif
	System::unlock();
}






