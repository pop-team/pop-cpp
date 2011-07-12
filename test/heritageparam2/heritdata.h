#ifndef _HERITDATA_H_
#define _HERITDATA_H_
#include "data.h"


class HeritData : /*public POPBase,*/ public Data
{
public:
	HeritData();
	~HeritData();
	int GetInternalData();
	void SetInternalData(int d);
	int GetMyData();
	void SetMyData(int d);
	virtual void Serialize(POPBuffer &buf, bool pack);


private:
	int myData;
};
#endif
