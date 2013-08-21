#ifndef _SERIALIZABLELIST_H_
#define _SERIALIZABLELIST_H_

#include "listclass.cc"  // Mandatory because of <template>!!

/* *********************************************************************
 * List of <typeData> values which inherites from POPBase and listClass
 * to make template ListClass serializable
 * 
 * Author: P.Kuonen   Date: March 2011
 * Modifications:
 *
 * *********************************************************************/  

#define typeData int

// !! current bug in POP-C++ imposes that POPBase is inherited first
class serializableList : public POPBase, public listClass<typeData>
{
  public:
    serializableList();
    serializableList(int s);
    ~serializableList();
    void Serialize(POPBuffer &buf, bool pack);
};

#endif
