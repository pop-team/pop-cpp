#ifndef _CLASSA_CC_
#define _CLASSA_CC_

#include <stdio.h>
#include "ClassA.h"

template <class C> ClassA<C>::ClassA() {printf("TemplateParam1: Contructing ClassA object\n");}

template <class C> ClassA<C>::~ClassA() {printf("TemplateParam1: Destroying ClassA object\n");}

template <class C> C* ClassA<C>::GetData()
{return &x;}

template <class C> void ClassA<C>::SetData(C d)
{x = d;}

#endif
