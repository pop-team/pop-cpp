#ifndef _STRUCTDATA_H_
#define _STRUCTDATA_H_
#include "data.h"


class StructData : public POPBase
{
public:
	StructData();
	~StructData();
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
