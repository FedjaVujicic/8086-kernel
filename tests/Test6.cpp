#include "system.h"

/*
 	 Test: idleThread
*/


void tick(){}

extern int syncPrintf(const char *format, ...);

class TestThread : public Thread
{
private:
	TestThread *t;

public:
	~TestThread()
	{
		waitToComplete();
	}

	void setT(TestThread* thr)
	{
		t = thr;
	}
protected:

	void run();

};

void TestThread::run()
{
	t->waitToComplete();
}


int userMain(int argc, char** argv)
{
	syncPrintf("Test starts.\n");
	TestThread *t1,*t2;
	t1 = new TestThread();
	t2 = new TestThread();
	t1->setT(t2);
	t2->setT(t1);
	t1->start();
	t2->start();
	delete t1;
	delete t2;
	syncPrintf("Test ends.\n");
	return 0;
}


