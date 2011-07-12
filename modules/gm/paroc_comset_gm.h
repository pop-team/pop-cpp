#ifndef PAROC_COMSET_GM_H
#define PAROC_COMSET_GM_H

#include "paroc_comset.h"
#include "paroc_combox.h"

#include "paroc_array.h"
#include "paroc_list.h"

typedef paroc_combox * COMBOXPTR;
typedef paroc_list<COMBOXPTR> combox_list;

/**
 * This class contains all active GM implementation
 */
class paroc_comset_gm:public paroc_comset{
public:
  /**
   * Constructor of this class
   */
  paroc_comset_gm();
  
  /**
   * Destructor of this class
   */
  ~paroc_comset_gm();
  
  /**
   * Allows to define the next protocol instance to treat
   * @param timeout The timeout
   */
  virtual paroc_combox* Wait(int timeout);
  
  /**
   * Allows to add a protocol instance given in argument into the set
   * 
   * @param combox A pointer to paroc_combox implementation
   */
  virtual bool Add(paroc_combox *combox);
  
  /**
   * Allows to remove a protocol instance given in argument into the set
   * 
   * @param combox A pointer to paroc_combox implementation
   */
  virtual bool Remove(paroc_combox *combox);
  
  /**
   * Allows to know the size of the set
   */
  virtual int GetSize();



  virtual paroc_combox* RemoveAt(int i);

  virtual paroc_combox* GetAt(int i);



protected:
  paroc_array<COMBOXPTR> comboxArray;//Array of protocol instance
  combox_list ready;//list of protocol instance ready
};
#endif // PAROC_COMBOXSET_GM_H
