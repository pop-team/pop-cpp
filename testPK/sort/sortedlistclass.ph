#ifndef _SORTEDLISTCLASS_H_
#define _SORTEDLISTCLASS_H_

/* *************************************************************************
 * Class parallel for sorting list of values (slow and quick version)
 *
 * Author: P.Kuonen     Date: March 2011
 * Modifications
 *
 * ************************************************************************/

#define typeData int
#include "serializablelist.h"

parclass sortedListClass
{
  classuid(1001);

  public:
    sortedListClass();
    sortedListClass(POPString machine) @{od.url(machine);};
    ~sortedListClass();
    async seq void setList(serializableList l);
    sync seq serializableList getList();

    sync seq int getListSize();

    async seq void sortList();         // Slow sort O(N*N)
    async seq void sortQuickList();    // Quick Sort O(N*Log(N))
    async seq void mergeLists(sortedListClass& other); // Merge two sorted lists

    sync seq   void printList();
    sync mutex void wait();

  private:
    serializableList theList;  // the list to sort

//  Internal merge (preserve the order):
//  Merge the lists "l1" and "l2" in "l1".
//  The two lists must be two sorted 'memory adjacent' lists 
//  IN: lists l1 and l2, lists sizes s1 and s2
//  OUT: merged lists in l1
    void mergeAdjacentLists(int* l1, int* l2, int s1, int s2);

};

#endif
