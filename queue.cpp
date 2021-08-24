#include "queue.h"
#include "PCB.h"
#include "system.h"
#include "SCHEDULE.h"

extern Queue sleepList;

Queue::Queue()
{
	lock();
	first = last = 0;
	size = 0;
	unlock();
}

Queue::~Queue()
{
	lock();
	Node* old;
	while (first != 0)
	{
		old = first;
		first = first->next;
		delete old;
	}
	size = 0;
	unlock();
}

unsigned Queue::getSize()
{
	return size;
}

void Queue::push(PCB* pcb)
{
	lock();
	if (pcb == 0)
	{
		unlock();
		return;
	}
	Node* cur = new Node(pcb);
	if (first == 0)
	{
		first = cur;
	}
	else
	{
		last->next = cur;
	}
	last = cur;
	++size;
	unlock();
}

PCB* Queue::pop()
{
	lock();
	if (first == 0)
	{
		unlock();
		return 0;
	}
	PCB* ret = first->pcb;
	Node* old = first;
	first = first->next;
	delete old;
	if (first == 0)
	{
		last = 0;
	}
	--size;
	unlock();
	return ret;
}

PCB* Queue::find(int x)
{
	lock();
	for (Node* cur = first; cur != 0; cur = cur->next)
	{
		if (x == cur->pcb->id)
		{
			unlock();
			return cur->pcb;
		}
	}
	unlock();
	return 0;
}

void Queue::remove(PCB* p)
{
	lock();
	if (first->pcb == p)
	{
		pop();
		unlock();
		return;
	}

	for (Node* cur = first; cur != last; cur = cur->next)
	{
		if (cur->next->pcb == p)
		{
			Node* old = cur->next;
			cur->next = cur->next->next;
			if (cur->next == 0)
			{
				last = cur;
			}
			delete old;
			--size;
			unlock();
			return;
		}
	}
	unlock();
}

void Queue::update()
{
	lock();
	if (this != &sleepList)
	{
		unlock();
		return;
	}
	for (Node* cur = first; cur != 0; cur = cur->next)
	{
		cur->pcb->timeToWait--;
		if (cur->pcb->timeToWait == 0)
		{
			cur->pcb->state = READY;
			cur->pcb->mySem->pcbWaiting->remove(cur->pcb);
			cur->pcb->mySem->value++;
			cur->pcb->mySem = 0;
			Scheduler::put(cur->pcb);
		}
	}
	unlock();
}
