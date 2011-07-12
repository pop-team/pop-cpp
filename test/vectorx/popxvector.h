#ifndef _POPXVECTOR_H_
#define _POPXVECTOR_H_
#include <vector>
#include "X.h"

using namespace std;


class POPxVector : public POPBase, public vector<X>
{
public:
	POPxVector();
	~POPxVector();
	virtual void Serialize(POPBuffer &buf, bool pack);

};
#endif
