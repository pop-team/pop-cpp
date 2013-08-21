// Parallel Sort of a list, version for POP-C++ testsuite
// Author: P.Kuonen
// Last update 18.8.2011
// argv[1] = list size
// argv[2] = NB of parallel objects
// argv[3] = [optional] mode="s" ->slow sort, quick sort otherwise (default) 
// --------------------------------------------------------------------------

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <timer.h>
#include "sortedlistclass.ph"
#define nbMaxMachines 200
#define MachinesList "machines.ip"

// -------------------------------------------------------------
// Read  the file 'fileName' containing the list of machines,
// fill the array 'machines' and returns the number of machines
int getAvailableMachines(char* fileName, POPString* machine[])
{
  int nbOfMachines = 0;
  FILE* f;
  if ( (f = fopen(fileName, "r"))!=NULL)
  {
    char* s;
    while (!feof(f))
    {
      s=(char*)malloc(100);
      fscanf(f, "%s", s);
      if (strlen(s)>0)
      {
        machine[nbOfMachines] = new POPString(s);
	      nbOfMachines++;
      }
    }
    fclose(f);
  } else
  {
    nbOfMachines=1;
    machine[0] = new POPString("localhost"); 
  }
  return nbOfMachines;
}


// Main program
int main(int argc, char* argv[])
{
  FILE *f;  
  char mode = 'q';

// --- Read and check arguments ---
  if (argc<3)
  {
    printf("Wrong parameters !!: Usage= parocrun objmap %s Size nbProc [s]\n\n",
            argv[0]);
    return 0;
  }

  int listSize = atoi(argv[1]);
  int nbProc = atoi(argv[2]);  

// nbProc must not be greater than the half of the list size 
// Absolute maximum =  nbMaxMachines
  int max;
  if (nbProc>nbMaxMachines) max=nbMaxMachines;
  if (listSize<(2*nbProc-1))
  {
    if (listSize<(2*nbMaxMachines)) max = listSize/2;
    printf("Wrong parameters !!: nbProc=%d is to big (maximum value=%d)\n\n", nbProc, max);
    return 0;
  }

  if (argc==4) mode=argv[3][0];  // "s" = slow sort otherwise quick sort

// --- End of arguments check

// --- Get the available machines
  POPString* machine[nbMaxMachines];  
  int nbOfMachines = getAvailableMachines(MachinesList, machine);
  
  printf("Available machines:\n");
  for (int i=0; i<nbOfMachines; i++)
    printf("  %d = %s \n", i, (const char*)(*machine[i])); 
// --- End of get machines 

// --- Creation of parallel objects containing partial unsorted lists 
  sortedListClass* listToSort[nbProc];

  for (int i=0; i<nbProc; i++)
    listToSort[i] = new sortedListClass(*(machine[i%nbOfMachines]));

// --- Start computation
  printf("\nSort: Start sorting in %d parallel objects\n", nbProc); 
  Timer timer;
  double initTime, mergeTime, sortTime, getTime;
  timer.Start(); //----------------------------------------- Start Timer

  // initialize lists To Sort 
  int normalSize = listSize/nbProc;
  int remnant = listSize % nbProc; 

  for (int i=0; i<nbProc; i++)
  {
    int s = normalSize;
    if (remnant>0) {s=normalSize+1; remnant--;}
    serializableList alist(s);            // Create the list
    alist.initRand(listSize*2);           // randomly initialize the list
    //alist.initDown(i*alist.getSize());  // initialize with descendant values
    listToSort[i]->setList(alist);
  }
  listToSort[nbProc-1]->wait(); // to synchronize (non mandatory)
  initTime = timer.Elapsed();  // ---------------------- Initialisation Time

// --- Sort the partial unsorted lists
  for (int i=0; i<nbProc; i++) 
    if (mode=='s') listToSort[i]->sortList();    // SLOW sort   (N*N)
    else listToSort[i]->sortQuickList();         // QUICK sort  (N*Log(N))

  listToSort[nbProc-1]->wait(); // to synchronize (not mandatory)
  sortTime = timer.Elapsed() - initTime;  // ------------ Sorting Time

// --- Merge the partial sorted lists
  if (nbProc%2>0) remnant=nbProc-1; else remnant=0; 
  int p=nbProc/2, k=1;

  for (int j=0; j<(int)log2(nbProc); j++)   
  {
    for (int i=0; i<p; i++)
      listToSort[2*i*k]->mergeLists(*listToSort[(2*i*k)+k]);

    if ((p%2)>0)
    {
      if (remnant>0) listToSort[2*k*(p-1)]->mergeLists(*listToSort[remnant]);       
      remnant=2*k*(p-1);
    }
    //listToSort[0]->wait(); // if we want to synchronize (not mandatory)
    k=k*2;
    p=p/2;
  }

  listToSort[0]->wait();  // to synchronize (not mandatory)
  mergeTime = timer.Elapsed() - sortTime - initTime;  // --- Merging Time
  timer.Stop();
  timer.Reset();

  printf("Sort: End of computation\n"); 
  printf("\nSort: Times: init=%g, sort=%g, merge=%g and total=%g (sec)\n\n",
            initTime, sortTime, mergeTime, initTime+sortTime+mergeTime);

  // Partially print the sorted list
  timer.Start(); //----------------------------------------- Start Timer
  serializableList sl=listToSort[0]->getList();
  getTime = timer.Elapsed(); // --- Time to get the list in the main
  timer.Stop();
  printf("Sort: Time to get the list=%g sec \n\n", getTime);
  sl.printList(20);

  // Check is the list is correctly sorted
  bool OK = true;
  for (int i=0; i>sl.getSize()-1; i++)
    if (sl.getVal(i)>sl.getVal(i+1))
    {
      OK = false; break;
    }
    if (OK)  printf("Sort: test succeeded, destroying objects...\n");
    else printf("Sort: test failed, destroying objects...\n");

  for (int i=0; i<nbProc; i++) delete listToSort[i];

  return  0; 
}
