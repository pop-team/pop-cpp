#ifndef _LISTCLASS_H_
#define _LISTCLASS_H_
/* ********************************************************************
 * Template class for the management of a list of <dataType>
 * Author: P.Kuonen    Date: March 2011
 * Modifications:
 *
 *********************************************************************/

template <class dataType>
class listClass //: public POPBase
{
  public:
    listClass();
    listClass(int s);
    ~listClass();

    inline int getSize();
    inline dataType getVal(int i);
    inline dataType* getSubList(int i);
    inline void setVal(int i, dataType val);
    inline void switchItem(int i1, int i2);

    inline void initRand(int max);
    inline void initVal(dataType val);
    inline void initUp(dataType first);
    inline void initDown(dataType first);

    inline void deleteList();
    void printList(int i);

  public:
    int size;
    dataType* theList;
};

#endif
