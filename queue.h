#pragma once
#include "global.h"

class PCB;

class Queue
{
public:
	Queue();
	~Queue();

	unsigned getSize();
	void push(PCB* x);
	PCB* pop();

private:
	struct Node
	{
		PCB* pcb;
		Node* next;
		Node(PCB* p)
		{
			lock();
			pcb = p;
			next = 0;
			unlock();
		}
	};

	Node* first, * last;
	unsigned size;
};
