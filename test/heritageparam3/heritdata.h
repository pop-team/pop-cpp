#ifndef _HERITDATA_H_
#define _HERITDATA_H_
#include "data.h"


class HeritData :  public Data
{
  public:
    HeritData();
    ~HeritData();
    int GetInternalData();
    void SetInternalData(int d);
    int GetMyData();
    double GetMyData(int i);
    void SetMyData(int d);
    void SetMyData(int d, double v);
    virtual void Serialize(POPBuffer &buf, bool pack);


  private:
    int myData;
    double toUseMemorySpace[100000];
};
#endif    
