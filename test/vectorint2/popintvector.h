#ifndef _POPINTVECTOR_H_
#define _POPINTVECTOR_H_
#include <vector>

using namespace std;


class POPintVector : public POPBase, public vector<int>
{
public:
	POPintVector();
	~POPintVector();
	int GetMyData();
	void SetMyData(int d);
	void ShowPOPintVector();
	virtual void Serialize(POPBuffer &buf, bool pack);


private:
	int myData;
};
#endif
