
#include "worker.ph"

Cworker::Cworker()
{
	myNo = 0;
}
Cworker::Cworker(int No)
{
	myNo = No;
}

void Cworker::Work(POP_Barrier &b)
{
	printf("Barrier: Worker %d: I am working before synchronisation..\n", myNo);   /*.. working ..*/
	b.activate();  /* synchronise all workers */
	printf("Barrier: Worker %d: I am working after synchronisation..\n", myNo); /*.. continue working ..*/
}

void Cworker::SetNo(int no)
{
	myNo=no;
}

int Cworker::GetNo()
{
	return myNo;
}

@pack(Cworker);

