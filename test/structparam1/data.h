#ifndef _DATA_H_
#define _DATA_H_


class Data
{
public:
	Data();
	~Data();
	int GetInternalData();
	void SetInternalData(int d);

private:
	int theData;
};
#endif
