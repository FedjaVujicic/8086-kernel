#ifndef QUEUE_H_
#define QUEUE_H_

class PCB;

class Queue
{
public:
	Queue();
	~Queue();

	unsigned getSize();
	void push(PCB* x);
	PCB* pop();
	PCB* find(int x);
	void remove(PCB* p);

	void update();

	void print();
private:
	struct Node
	{
		PCB* pcb;
		Node* next;
		Node(PCB* p)
		{
			pcb = p;
			next = 0;
		}
	};

	Node* first, * last;
	unsigned size;
};

#endif
