#ifndef PROBOBJ_PH
#define PROBOBJ_PH
#include "paroc_list.h"

parclass ProbObj;
typedef paroc_list<ProbObj *> CProbList;

parclass ProbObj
{
public:
	ProbObj();
	~ProbObj();
	conc async void Exec();

	void IncreaseDependencyCounter();
	virtual void AddNext(ProbObj &p);

	void ResetCounter();

	classuid(5);

protected:
	virtual void TriggerNexts();
	virtual void Solve();
protected:
	int count, savedcounter;
//	float flops;
//	float time;

	CProbList nexts;
};


#endif

