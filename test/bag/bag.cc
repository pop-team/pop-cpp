#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define size 40
#define val 1000  // max 32000
#define nbBags 4


parclass Bag
{
 public:
  Bag();
  ~Bag();
  async seq void initBag(int myid, int theSize);   // constructor
  async seq void setNext(Bag &b);
  async conc void setMax(int m);
  sync seq int getMax();

  async seq void search();

  sync seq void wait();

  async mutex void showBag();

  void Destroy();

 private:
  int* theBag;
  Bag *next;
   
  int max;
  int actualSize;

  int id;
}; 

Bag::Bag()
{
  printf("Create bags..\n");
  actualSize=0;
  theBag = NULL;
  next=NULL;
  max=-1000;
  
  id=-1;
}

Bag::~Bag()
{
  printf("Destroy bags..\n");
  Destroy();
}

void Bag::Destroy()
{
  if (next!=NULL) delete next;
  next=NULL;
}

void Bag::initBag(int myid, int theSize)
{

  printf("Init bag #%d of size %d.\n", myid, theSize);
  id=myid;

  actualSize=theSize;
  theBag = new int[actualSize];
  max=-1;
  srand(myid+time(NULL));
  for (int i=0; i<actualSize; i++)
    theBag[i]=rand()% val;
}

void Bag::setNext(Bag &b) 
{
  next = new Bag(b);
}

void Bag::setMax(int m)
{
  mutex 
    {
      if (m>max)
	{
	  printf("Bag #%d: SetMax = %d.\n", id, m);
	  max=m;
	  if (next!=NULL) next->setMax(m);
	}
    }
}

int Bag::getMax()
{
//printf("GetMax in Bag no= %d.\n", no);
  return max;
}

void Bag::search()
{

  rprintf("Search in bag no=%d..\n", id);

  if (next!=NULL && id>0) next->search();
  int i=0;
  int localmax=theBag[0];
  while (i<actualSize)
  {
    usleep(1000);
    mutex 
      {
	if (theBag[i]>max) setMax(theBag[i]);
      }
    i++;
  }
}

void Bag::wait()
{
  if (id>0 && next!=NULL) next->wait();
}

void Bag::showBag()
{
  for (int i=0;i<actualSize;i++)
  {
    rprintf("#%d (%d) = %d\n",id,i,theBag[i]);
  }
}

int main(int, char **)
{
  int x = 0;
  Bag bags[nbBags];

  for (int i=0; i<(nbBags); i++)
    bags[i].initBag(i, size/nbBags);


  for (int i=1; i<(nbBags); i++)
    bags[i].setNext(bags[i-1]);

  bags[0].setNext(bags[nbBags-1]);

  for (int i=0; i<(nbBags); i++)
    bags[i].showBag();

  printf("Start search on bag size of %d\n", size/nbBags);
  bags[nbBags-1].search();
  bags[nbBags-1].wait();

  x=bags[0].getMax();
  printf("Find : %d\n",x);


  for (int i=0; i<(nbBags); i++)
    bags[i].Destroy();

  return 0;
}

@pack(Bag);
