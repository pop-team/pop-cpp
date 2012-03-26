#include <stdio.h>
#include <assert.h>
#include "probobj.ph"

ProbObj::ProbObj()
{
	count=0;
	savedcounter=0;
}

ProbObj::~ProbObj()
{
	POSITION pos=nexts.GetHeadPosition();
	while (pos!=NULL)
	{
		ProbObj *tmp=nexts.GetNext(pos);
		delete tmp;

	}
}

void ProbObj::Exec()
{
	bool cansolve;
	mutex {
		if (count<savedcounter) count++;
		cansolve=(count>=savedcounter);
	}
	if (cansolve)
	{
		Solve();
		ResetCounter();
		TriggerNexts();
		DEBUG("Solved");
	}
}

void ProbObj::TriggerNexts()
{
	DEBUG("Checking next dependencies\n");
	POSITION pos=nexts.GetHeadPosition();
	while (pos!=NULL)
	{
		ProbObj *p=nexts.GetNext(pos);
		DEBUG("Now solve next\n");
		assert(p!=NULL);
		p->Exec();
	}
}

void ProbObj::IncreaseDependencyCounter()
{
	savedcounter++;
}

void ProbObj::AddNext(ProbObj &p)
{
	printf("Add next problem to dependency list\n");

	ProbObj *obj=new ProbObj(p.GetAccessPoint());
	assert(obj!=NULL);
	nexts.AddTail(obj);
	p.IncreaseDependencyCounter();
}

void ProbObj::ResetCounter()
{
	count=0;
}



void ProbObj::Solve()
{
}

