/** 
 * @author  P.kuonen
 * @date    2012.09.04
 * This program test the implementaion of a barrier using synchronizers
 */
#include <stdio.h>
#include "Barrier.ph"
#include "worker.ph"

int main(int argc, char** argv)
{
  printf("Barrier: Starting test...\n");
  int Nb_workers=15;
  if (argc > 1) Nb_workers = atoi(argv[1]);
  
  POP_Barrier Bar(Nb_workers);     /*Initialise the barrier */  
  Cworker theWorkers[Nb_workers];  /* Create the workers */
  
  for (int i = 0; i<Nb_workers; i++) /*start Working*/
  {
    theWorkers[i].SetNo(i);
    theWorkers[i].Work(Bar);
  }
  if (theWorkers[1].GetNo()==1) 
  {
    printf("Barrier: test succeeded, destroying objects...\n");
    return 0;
  }
  else
  {
    printf("Barrier: test failed, destroying objects...\n");
    return 1;
  }

}
