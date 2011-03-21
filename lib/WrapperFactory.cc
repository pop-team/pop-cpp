/**
 * File : WrapperFactory.cc
 * Author : Adrian Wyssen
 * Description : Concrete implementation of a WrapperFactory
 * Creation date : 04/08/2010
 * 
 * Modifications :
 * Authors		Date			Comment
 */

#include "WrapperFactory.h"
#include "ESXWrapper.h"


VPopCWrapper* WrapperFactory::createWrapper(wrapper_type type, paroc_accesspoint clonerRef){
   switch(type){
      case ESXWRAPPER: return new ESXWrapper(clonerRef); break;
      default : return new ESXWrapper(clonerRef);
   }
   
   return new ESXWrapper(clonerRef);
}
