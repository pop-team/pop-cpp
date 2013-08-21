#ifndef _BAG_PH
#define _BAG_PH

typedef enum bagStatus {idle, searching, terminated, stop} typeStatus;

parclass Bag
{classuid(1001);

 public:
   Bag()@{od.url("localhost");};
  ~Bag();
  async seq  void initBag(int myId, int Size);  
  async seq  void setNext(Bag &b);

  async seq void search(); 
  sync seq  int getResult();
  sync conc int getMyMax();
  sync conc bool waitResult(int m);

private:      
  int* theBag;           // my bag of int   
  int actualSize;        // my size of the set to search in
  Bag* next;             // my neighbour on the ring
  int max;               // my current max value
  typeStatus status;     // my current status
  int id;                // my identity (number)
};

#endif
