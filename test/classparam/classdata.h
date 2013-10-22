#ifndef _CLASSDATA_H_
#define _CLASSDATA_H_
#include "data.h"


class ClassData : public POPBase
{
  public:
    ClassData();
    ~ClassData();
    Data GetInternalData();
    void SetInternalData(Data d);
    int GetMyData();
    void SetMyData(int d);
    virtual void Serialize(POPBuffer &buf, bool pack);


  private:
    Data theData;
    int myData;
};
#endif    
