/*
	# Author:   Wyssen Adrian
	# Date:     04.08.2010
	# Filename: WrapperFactory.h
	# Purpose:  Header for concrete implementation of a WrapperFactory
	# Version:  v1.0
*/

#ifndef WRAPPERFACTORY_H
#define WRAPPERFACTORY_H



#include "VPopCWrapper.h"



class WrapperFactory{

public:
   enum wrapper_type{
      ESXWRAPPER
   };
   
   /* factory method creating an instance of a VPopCWrapper of type wrapper_type */
   virtual VPopCWrapper* createWrapper(wrapper_type type, paroc_accesspoint clonerRef);
};

#endif /* WRAPPERFACTORY_H */
