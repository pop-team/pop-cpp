#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "Bag.ph"

// -- ----------------------------------------------------
Bag::Bag()
{
  id = -1;
  max = -1;
  next = NULL;
  status = idle;
}

// -- ----------------------------------------------------
Bag::~Bag()
{
  printf("Bag: Destroying Bag %d...\n",id);
}
		
// -- ----------------------------------------------------
void Bag::setNext(Bag &b)
{ next = new Bag(b);}

// -- ----------------------------------------------------
int Bag::getMyMax()
{ return max;}

// -- ----------------------------------------------------
void Bag::initBag(int myId, int size)
// Fill de bag with random values
{
  int m = 0;
  id = myId;
  actualSize = size;
  theBag=(int*)malloc(actualSize*sizeof(int));
  srand(id*3);
  for (int i=0; i<actualSize; i++)
  {
    theBag[i]=(rand() % (9900000+rand()%(10000)));
    if (theBag[i] > m) m=theBag[i];
  }
  // Display the maximum for demonstration purpose 
  printf("Bag: Maximum value in bag %d of size %d = %d\n", id, actualSize, m);         
}

// -- ----------------------------------------------------
bool Bag::waitResult(int m)
{
  //if (m>max) max=m;
  if (m>this->getMyMax()) max=m;
  printf("Bag: waitResult in Bag %d, max = %d\n",id, max);
  bool result = false;
  switch (status)
  {
     case idle  :;
     case searching  : {result = false; break;}
     case terminated : {while (! next->waitResult(max));
                        result = true;
                        status = stop; break;}
     case stop       : {result = true; break;}
  }
  return result;
}

// -- ----------------------------------------------------
int Bag::getResult()
{
  printf("Bag: getResult in Bag %d\n",id);
  status = stop;
  while (! next->waitResult(max));
  return max;
}


// -- ----------------------------------------------------
void Bag::search() 
{
  if (status==idle)
  {
    status=searching;
    next->search();
    max = 0;
    printf("Bag: Start search in Bag %d\n",id);
    for (int i=0; i<actualSize; i++)
      if (theBag[i]>max) max=theBag[i];
      //if (theBag[i]>this->getMyMax()) max=theBag[i];
    printf("Bag: End search in Bag %d (max=%d)\n",id, max);
  }
  status = terminated;
}

@pack(Bag);
