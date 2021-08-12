#include "queue.h"

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

void Queue::push(PCB* info)
{
	lock();
	Node* cur = new Node(info);
	if (first == 0)
	{
		first = last = cur;
	}
	else
	{
		last->next = cur;
		last = cur;
	}
	++size;
	unlock();
}

PCB* Queue::pop()
{
	lock();
	if (first == 0)
	{
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
