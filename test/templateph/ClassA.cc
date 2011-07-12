#ifndef _CLASSA_CC_
#define _CLASSA_CC_

#include "ClassA.h"
#include <stdio.h>


template <class C> ClassA<C>::ClassA() {printf("Template: Contructing ClassA object\n");}

template <class C> ClassA<C>::~ClassA() {printf("Template: Destroying ClassA object\n");}

template <class C> void ClassA<C>::SetIdent(int i) {x.SetIdent(i); printf("Template: SetIdent on ClassA object %d\n",i);}

template <class C> int ClassA<C>::GetIdent() {printf("Template: GetIdent on ClassA object %d\n",x.GetIdent());return x.GetIdent();}

#endif
