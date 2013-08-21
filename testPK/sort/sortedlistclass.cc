#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <timer.h>
#include "sortedlistclass.ph"
  
//- Constructors and Destructors ---------------------------------------
sortedListClass::sortedListClass() // default
{}

//----------------------------------------------------------------------
sortedListClass::sortedListClass(POPString machine) // to create on 'machine'
{
  printf("Sort: sortedList object created on machine:%s\n",POPGetHost());
}

//----------------------------------------------------------------------
sortedListClass::~sortedListClass() // destructor
{theList.deleteList();}

//--Utility methods-----------------------------------------------------

//----------------------------------------------------------------------
void sortedListClass::setList(serializableList l)
{theList.deleteList(); theList=l;}

//----------------------------------------------------------------------
serializableList sortedListClass::getList()
{return theList;}

//----------------------------------------------------------------------
int sortedListClass::getListSize()
{return theList.getSize();}

//----------------------------------------------------------------------
void sortedListClass::printList()
// print at maximum 60 elements of the list
{ 
  int l;
  if (theList.getSize()>60) l=30; else l=theList.getSize()/2;
  theList.printList(l);
}
 
//----------------------------------------------------------------------
void sortedListClass::wait()
{ 
  //printf("Waiting... \n");
}

//--Methods to sort the list--------------------------------------------

void sortedListClass::mergeLists(sortedListClass& other)
//----------------------------------------------------------------------
// External merge (preserve the order):
// Merge the current list with the list of the 'other' parallel object
// (both lists must be sorted, )
// IN:  'theList' (my List) and 'thelist' of the 'other' parallel object
// OUT: 'theList' merged with 'theList' of 'other' 
{
  serializableList otherList=other.getList(); // get the list to merge with
  if (other.getListSize()>0)
  {
    int index1=0, index2=0;
    serializableList* merged =
                 new serializableList(theList.getSize()+other.getListSize());
    while ( (index1<theList.getSize()) && (index2<otherList.getSize()) )
    {
       if ( theList.getVal(index1)<otherList.getVal(index2) )
       {
         merged->setVal(index1+index2, theList.getVal(index1));
         index1++;
       }
       else
       {
         merged->setVal(index1+index2, otherList.getVal(index2));
         index2++;
       }
    }
    if (index1==theList.getSize()) 
      for (int i=index2; i<otherList.getSize(); i++)
        merged->setVal(index1+i,otherList.getVal(i));
    else
      for (int i=index1; i<theList.getSize(); i++)
        merged->setVal(index2+i,theList.getVal(i));
    theList.deleteList();
    theList = *merged;
  }
}

void sortedListClass::mergeAdjacentLists(int l1[], int l2[], int s1, int s2)
//----------------------------------------------------------------------
//  Internal merge (preserve the order):
//  Merge the lists "l1" and "l2" in "l1".
//  The two lists must be two sorted 'memory adjacent' lists 
//  IN: lists l1 and l2, lists sizes s1 and s2
//  OUT: merged lists in l1
{
  //for (int i=0; i<s1; i++) printf("%d ", l1[i]); printf("<->");
  //for (int i=0; i<s2; i++) printf("%d ", l2[i]); printf("= ");

  int* lt = (int*)malloc(s1*sizeof(int)); // temporary list
  int i1=0, i2=0, ita=0, itb=0;

  while (((i2+s1)>i1) && (i2<s2) )
  {
    if (i1>=s1)
    {
      if (lt[itb] > l2[i2]) 
      {
        l1[i1]=l2[i2]; i2++;
      }
      else
      {
        l1[i1]=lt[itb];
        itb++;
      }
      i1++;
    }
    else
    if (ita>itb)
    {
      if (l2[i2]>lt[itb])
      {
        if (lt[itb]<l1[i1])
        {
          lt[ita]=l1[i1];
          l1[i1]=lt[itb];
          itb++; ita++;
        }
        i1++;
      }      
      else
      {
        if (l2[i2]<l1[i1])
        {
          lt[ita]=l1[i1];
          l1[i1]=l2[i2];
          ita++; i2++;       
        }
        i1++;          
      }
    }
    else
    if (l2[i2]<l1[i1])
    {
      lt[ita]=l1[i1];
      l1[i1]=l2[i2];
      ita++; i1++; i2++;      
    }
    else i1++;
  }
  for (int i=i1; i<s1; i++)
  {
    lt[ita]=l1[i];
    ita++;
  }
  for (int i=itb; i<ita; i++)
  {
    l1[i1]=lt[i];
    i1++;
  }

  //for (int i=0; i<s1+s2; i++) printf("%d ", l1[i]);
  //int c; scanf("%c", &c);
  free(lt);
}

//----------------------------------------------------------------------
// Rapid sort of the list O(N*log2(N))
void sortedListClass::sortQuickList()
{    
  int listSize = theList.getSize();
  int p=listSize/2, k=1;
  for (int j=0; j<(int)log2(listSize); j++)
  {
    // Merges lists of size k
    for (int i=0; i<p; i++)
      mergeAdjacentLists(theList.getSubList(2*i*k),
                          theList.getSubList((2*i*k)+k),
                          k, k);

    // Merge the last merged list with the possible remnant
    mergeAdjacentLists(theList.getSubList(2*(p-1)*k),
                       theList.getSubList((2*(p-1)*k)+2*k),
                       2*k, listSize-(2*(p-1)*k+2*k) );
 
    k=k*2;
    p=p/2;
  }  
}


//----------------------------------------------------------------------
// Slow sort of the list O(N*N) (sort by permutation)
void sortedListClass::sortList()
{
  int nbSwitch;

  do {
   nbSwitch=0;
   for (int i=0; i<theList.getSize()-1; i++)
    {
    if ( theList.getVal(i) > theList.getVal(i+1) )
      {
      theList.switchItem(i, i+1);
      nbSwitch++;
      }
    }
  } while (nbSwitch>0);
}

@pack(sortedListClass);
