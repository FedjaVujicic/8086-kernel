#include <iostream.h>
#include <dos.h>
#include "SCHEDULE.H"


class PCB
{
public:
	unsigned sp;
	unsigned ss;
	unsigned bp;
	unsigned finished;
	int timeSlice;
};

PCB *p[3];
volatile PCB* running; 

volatile unsigned tsp;
volatile unsigned tss;
volatile unsigned tbp;

volatile int counter = 20;
volatile int context_switch_requested = 0;

typedef void interrupt (*pInterrupt)(...); // for setvect and getvect
pInterrupt oldRoutine = 0; // for setvect and getvect


void lock()
{
#ifndef BCC_BLOCK_IGNORE
	asm cli;
#endif
}

void unlock()
{
#ifndef BCC_BLOCK_IGNORE
	asm sti;
#endif
}


void interrupt timer()
{
	if (!context_switch_requested)
	{
		counter--;
	}

	if (counter == 0 || context_switch_requested)
	{
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov tsp, sp
			mov tss, ss
			mov tbp, bp
		}
#endif
		running->sp = tsp;
		running->ss = tss;
		running->bp = tbp;

		if (!running->finished)
		{
			Scheduler::put((PCB*) running);
		}
		running = Scheduler::get();
  
		tsp = running->sp;
		tss = running->ss; 
		tbp = running->bp;

		counter = running->timeSlice;
#ifndef BCC_BLOCK_IGNORE
		asm {
			mov sp, tsp
			mov ss, tss
			mov bp, tbp
		}
#endif
	} 
    
	// poziv stare prekidne rutine koja se 
    // nalazila na 08h, a sad je na 60h
    // poziva se samo kada nije zahtevana promena
    // konteksta – tako se da se stara
    // rutina poziva samo kada je stvarno doslo do prekida
	if(!context_switch_requested)
	{
#ifndef BCC_BLOCK_IGNORE
		asm int 60h;
#endif
	}
		                                              
	context_switch_requested = 0;
}

void dispatch() // sinhrona promena konteksta
{
	lock();
	context_switch_requested = 1;
	timer();
	unlock();
}

unsigned oldTimerOFF, oldTimerSEG; // stara prekidna rutina

// postavlja novu prekidnu rutinu
void initialize()
{
#ifndef BCC_BLOCK_IGNORE
	asm{
		cli
		push es
		push ax

		mov ax,0   //inicijalizuje rutinu za tajmer
		mov es,ax

		mov ax, word ptr es:0022h //pamti staru rutinu
		mov word ptr oldTimerSEG, ax	
		mov ax, word ptr es:0020h	
		mov word ptr oldTimerOFF, ax	

		mov word ptr es:0022h, seg timer	 //postavlja novu rutinu
		mov word ptr es:0020h, offset timer

		mov ax, oldTimerSEG	 //	postavlja staru rutinu na int 60h
		mov word ptr es:0182h, ax
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
#endif
}

// vraca staru prekidnu rutinu
void restore()
{
#ifndef BCC_BLOCK_IGNORE
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
#endif
}

void exitThread()
{
	running->finished = 1;
	dispatch();
}  

void a()
{
	for (int i =0; i < 30; ++i)
	{
		lock();
		cout << "u a() i = " << i << endl;
		unlock();

#ifndef BCC_BLOCK_IGNORE
		for (int k = 0; k < 10000; ++k)
			for (int j = 0; j < 30000; ++j);
#endif
	}
	exitThread();
}

void b()
{
	for (int i = 0; i < 30; ++i)
	{
		lock();
		cout << "u b() i = " << i << endl;
		unlock();

#ifndef BCC_BLOCK_IGNORE
		for (int k = 0; k < 10000; ++k)
			for (int j = 0; j < 30000; ++j);
#endif
	}
	exitThread();
}


void createProcess(PCB *newPCB, void (*body)())
{
	unsigned* st1 = new unsigned[1024];

	st1[1023] = 0x200;//setovan I fleg u pocetnom PSW-u za nit

#ifndef BCC_BLOCK_IGNORE
	st1[1022] = FP_SEG(body);
	st1[1021] = FP_OFF(body);

	newPCB->sp = FP_OFF(st1 + 1012); //svi sacuvani registri pri ulasku u interrupt rutinu
	newPCB->ss = FP_SEG(st1 + 1012);
	newPCB->bp = FP_OFF(st1 + 1012);
#endif
	newPCB->finished= 0;
}



void doSomething()
{
	lock();
	p[1] = new PCB();
	createProcess(p[1],a);
	cout<<"napravio a"<<endl;
	p[1]->timeSlice = 40;
	Scheduler::put(p[1]);

	p[2] = new PCB();
	createProcess(p[2],b);
	cout<<"napravio b"<<endl;
	p[2]->timeSlice = 20;
	Scheduler::put(p[2]);

	p[0] = new PCB();
	p[0]->timeSlice = 20;
	p[0]->finished = 0;

	running = p[0];
	unlock();

#ifndef BCC_BLOCK_IGNORE
	for (int i = 0; i < 30; ++i)
	{
		lock();
		cout << "main " << i << endl;
		unlock();

		for (int j = 0; j < 30000; ++j)
			for (int k = 0; k < 30000; ++k);
	}
#endif
	cout<<"Happy End"<<endl;
}

int main(){
	
	initialize();

	doSomething();

	restore();

	return 0;
}

