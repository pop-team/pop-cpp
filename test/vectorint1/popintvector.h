#ifndef _POPINTVECTOR_H_
#define _POPINTVECTOR_H_
#include <vector>

using namespace std;


class POPintVector : public POPBase
{
public:
	POPintVector();
	~POPintVector();
	vector<int> GetInternalData();
	void SetInternalData(vector<int> d);
	int GetMyData();
	void SetMyData(int d);
	void ShowPOPintVector();
	virtual void Serialize(POPBuffer &buf, bool pack);


private:
	vector<int> theData;
	int myData;
};
#endif
