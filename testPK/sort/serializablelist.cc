#ifndef _SERIALIZABLELIST_CC_
#define _SERIALIZABLELIST_CC_

#include "serializablelist.h"
   
serializableList::serializableList() : listClass<typeData>::listClass() {}
serializableList::serializableList(int s) : listClass<typeData>::listClass(s) {}
serializableList::~serializableList() {/* listClass<typeData>::~listClass();*/}

void serializableList::Serialize(POPBuffer& buf, bool pack)
{
   if (pack)
   {
     buf.Pack(&size,1);
     buf.Pack(theList, size);
   }
   else
   {
     deleteList();
     buf.UnPack(&size, 1);
     if (size>0)
     {
       theList = (typeData*)malloc(size*sizeof(typeData));
       buf.UnPack(theList, size);
      } 
   }
};

#endif

