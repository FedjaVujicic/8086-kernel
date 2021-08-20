#include "queue.h"
#include "PCB.h"
#include "system.h"

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
