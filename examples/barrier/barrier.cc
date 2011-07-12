#include "barrier.ph"

POP_Barrier::POP_Barrier()
{
	counter = 1;
	printf("\nBarrier: Closed for %d workers\n", counter);
}

POP_Barrier::POP_Barrier(int n)
{
	counter = n;
	printf("\nBarrier: Closed for %d workers\n", counter);
}

void POP_Barrier::activate()
{
	event.lock();
	counter--;
	if (counter==0) {printf("\nBarrier: Open the barrier;\n"); event.raise();}
	else event.wait();
	event.unlock();
}

@pack(POP_Barrier);

