/*
 * TestSem.cpp
 *
 *  Created on: Aug 17, 2021
 *      Author: OS1
 */
#include <iostream.h>
#include "system.h"

void tick() {}

extern int syncPrintf(const char *format, ...);

class TestThread : public Thread
{
public:
	TestThread() : Thread(defaultStackSize, defaultTimeSlice)
	{}
	void run()
	{
		for (int i = 0; i < 10; i++)
		{
			lock();
			cout << "It's gonna die" << endl;
			unlock();
			syncPrintf("Running thread id = %d\n", getId());
			lock();
			cout << "T" << endl;
			unlock();
			syncPrintf(". . . . . \n");
			for (int j = 0; j < 2000; j++)
				for (int k = 0; k < 20000; k++);
		}
	}
	~TestThread()
	{
		waitToComplete();
	}
};

int userMain(int argc, char** argv)
{
	syncPrintf("Omae wa mo shinderu \n");
	lock();
	cout << "Anxious start " << endl;
	unlock();
	syncPrintf("YEP \n");
	lock();
	cout << "haAHhaA" << endl;
	unlock();

	TestThread* t1, * t2, * t3, * t4, * t5, * t6, * t7, * t8, * t9, * t10, * t11, * t12, * t13, * t14, * t15, * t16, * t17, * t18, * t19, * t20, * t21, * t22, * t23, * t24, * t25, * t26, * t27, * t28, * t29;
	TestThread* t30, * t31, * t32, * t33, * t34, * t35, * t36, * t37, * t38, * t39, * t40, * t41, * t42, * t43, * t44, * t45, * t46, * t47, * t48, * t49, * t50;

	t1 = new TestThread();
	t2 = new TestThread();
	t3 = new TestThread();
	t4 = new TestThread();
	t5 = new TestThread();
	t6 = new TestThread();
	t7 = new TestThread();
	t8 = new TestThread();
	t9 = new TestThread();
	t10 = new TestThread();
	t11 = new TestThread();
	t12 = new TestThread();
	t13 = new TestThread();
	t14 = new TestThread();
	t15 = new TestThread();
	t16 = new TestThread();
	t17 = new TestThread();
	t18 = new TestThread();
	t19 = new TestThread();
	t20 = new TestThread();
	t21 = new TestThread();
	t22 = new TestThread();
	t23 = new TestThread();
	t24 = new TestThread();
	t25 = new TestThread();
	t26 = new TestThread();
	t27 = new TestThread();
	t28 = new TestThread();
	t29 = new TestThread();
	t30 = new TestThread();
	t31 = new TestThread();
	t32 = new TestThread();
	t33 = new TestThread();
	t34 = new TestThread();
	t35 = new TestThread();
	t36 = new TestThread();
	t37 = new TestThread();
	t38 = new TestThread();
	t39 = new TestThread();
	t40 = new TestThread();
	t41 = new TestThread();
	t42 = new TestThread();
	t43 = new TestThread();
	t44 = new TestThread();
	t45 = new TestThread();
	t46 = new TestThread();
	t47 = new TestThread();
	t48 = new TestThread();
	t49 = new TestThread();
	t50 = new TestThread();



	t1->start();
	t2->start();
	t3->start();
	t4->start();
	t5->start();
	t6->start();
	t7->start();
	t8->start();
	t9->start();
	t10->start();
	t11->start();
	t12->start();
	t13->start();
	t14->start();
	t15->start();
	t16->start();
	t17->start();
	t18->start();
	t19->start();
	t20->start();
	t21->start();
	t22->start();
	t23->start();
	t24->start();
	t25->start();
	t26->start();
	t27->start();
	t28->start();
	t29->start();
	t30->start();
	t31->start();
	t32->start();
	t33->start();
	t34->start();
	t35->start();
	t36->start();
	t37->start();
	t38->start();
	t39->start();
	t40->start();
	t41->start();
	t42->start();
	t43->start();
	t44->start();
	t45->start();
	t46->start();
	t47->start();
	t48->start();
	t49->start();
	t50->start();


	delete t1;
	delete t2;
	delete t3;
	delete t4;
	delete t5;
	delete t6;
	delete t7;
	delete t8;
	delete t9;
	delete t10;
	delete t11;
	delete t12;
	delete t13;
	delete t14;
	delete t15;
	delete t16;
	delete t17;
	delete t18;
	delete t19;
	delete t20;
	delete t21;
	delete t22;
	delete t23;
	delete t24;
	delete t25;
	delete t26;
	delete t27;
	delete t28;
	delete t29;
	delete t30;
	delete t31;
	delete t32;
	delete t33;
	delete t34;
	delete t35;
	delete t36;
	delete t37;
	delete t38;
	delete t39;
	delete t40;
	delete t41;
	delete t42;
	delete t43;
	delete t44;
	delete t45;
	delete t46;
	delete t47;
	delete t48;
	delete t49;
	delete t50;

	syncPrintf("Test ended \n");

	lock();
	cout << "Die" << endl;


	cout << "Y U EVEN TRYING " << endl;
	unlock();
	syncPrintf("Mad cuz bad \n");

	return 0;
}

