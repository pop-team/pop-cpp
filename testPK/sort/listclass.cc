#ifndef _LISTCLASS_C_
#define _LISTCLASS_C_

#include <stdlib.h>
#include <stdio.h>
#include "listclass.h"

// Constructors ---------------------------------------------------------
template <class dataType> listClass<dataType>::listClass()
{
  size = 0;
  theList = NULL;
}

template <class dataType> listClass<dataType>::listClass(int s)
{
  size = s;
  theList = (dataType*)malloc(s*sizeof(dataType));
  if (theList == NULL)
  { 
    printf("Memory overflow: malloc failed\n");
    exit(0);
  }
}

// Destructor -----------------------------------------------------------
template <class dataType> listClass<dataType>::~listClass()
{ /*if (theList != NULL) free(theList);*/ size=0; theList=NULL;}

// Methods --------------------------------------------------------------

template <class dataType> int listClass<dataType>::getSize()
{return size;}

template <class dataType> dataType listClass<dataType>::getVal(int i)
{return theList[i];}

template <class dataType> dataType* listClass<dataType>::getSubList(int i)
{return &theList[i];}

template <class dataType> void listClass<dataType>::setVal(int i, dataType val)
{theList[i]=val;}

template <class dataType> void listClass<dataType>::initRand(int max=100000)
{for (int i = 0; i<size; i++) theList[i]=(dataType)rand()%max;}

template <class dataType> void listClass<dataType>::initUp(dataType first)
{for (int i = 0; i<size; i++) theList[i]=first + (dataType)i;}

template <class dataType> void listClass<dataType>::initDown(dataType first)
{for (int i = 0; i<size; i++) theList[i]=(dataType)size - (dataType)i + first;}

template <class dataType> void listClass<dataType>::initVal(dataType val)
{for (int i = 0; i<size; i++) theList[i]=val;}

template <class dataType> void listClass<dataType>::deleteList()
{if (theList != NULL) free(theList); size=0; theList=NULL;}
 
template <class dataType> void listClass<dataType>::switchItem(int i1, int i2)
{
  dataType temp;

  temp = theList[i1];
  theList[i1] = theList[i2];
  theList[i2] = temp;
}

template <class dataType> void listClass<dataType>::printList(int i)
{
  printf("List of size %d is:\n", size);
  if (i>size/2) i = size/2;
  printf("Size:%d->", size);
  for (int j=0; j<i; j++) printf("%d ",(int)theList[j]);
  printf("...");
  for (int j=size-i; j<size; j++) printf("%d ",(int)theList[j]);
  printf("\n");
}

#endif
