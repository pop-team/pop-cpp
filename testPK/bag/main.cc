#include <stdio.h>
#include "Bag.ph"
#define size 100000000
#define nbBags 10

int main(int argc, char **argv)
{
  printf("\nBag: Starting test....\n");


  int maxVal = -1;
  int theMax = -1;
  
  Bag* bags[nbBags];
   for (int i=0; i<nbBags; i++) bags[i] = new Bag;

  printf("Bag: Array of %d Bags created\n", nbBags);
	
  for (int i=0; i<nbBags; i++) bags[i]->initBag(i, size/nbBags);
  
  for (int i=1; i<=nbBags; i++)  bags[i%nbBags]->setNext(*bags[i-1]);
  printf("Bag: Ring of Bags created\n");   
 
  bags[nbBags-1]->search();
  theMax =  bags[nbBags-1]->getResult();
 
 for (int i=0; i<nbBags; i++)
  {
    if (bags[i]->getMyMax() > maxVal) maxVal=bags[i]->getMyMax();
    delete bags[i];
  }

  if (maxVal == theMax) 
    printf("Bag: test succeeded (max=%d), destroying objects...\n",
           theMax);
  else
    printf("Bag: test failed (%d < %d), destroying objects...\n",
            theMax, maxVal);

  return 0;
}
