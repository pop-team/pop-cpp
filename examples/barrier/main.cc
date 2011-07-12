#include <stdio.h>
#include "barrier.ph"
#include "worker.ph"

int main(int argc, char** argv)
{
	printf("Barrier: Starting ...\n");
	int Nb_workers=15;
	if (argc > 1) Nb_workers = atoi(argv[1]);

	POP_Barrier Bar(Nb_workers);     /*Initialise the barrier */
	Cworker theWorkers[Nb_workers];  /* Create the workers */

	for (int i = 0; i<Nb_workers; i++) /*start Working*/
	{
		theWorkers[i].SetNo(i);
		theWorkers[i].Work(Bar);
	}
	printf("Barrier: Value of theWorkers[1].GetNo()=%d\n",theWorkers[1].GetNo());
	printf("Barrier: terminated, destroying objects...\n");
	return 0;
}
