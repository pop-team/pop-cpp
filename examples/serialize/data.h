#ifndef _DATA_H
#define _DATA_H

class Data : public POPBase
{
public:
	Data();
	~Data();

	int GetInternalData();
	void SetInternalData(int d);
	virtual void Serialize(POPBuffer &buf, bool pack);

private:
	int theData;
};
#endif
