#ifndef _TRANSMISSIBLE_H
#define _TRANSMISSIBLE_H
#include "ClassA.h"
#include "X.h"

class Transmissible : public POPBase, public ClassA<X>
{
public:
	Transmissible();
	~Transmissible();
	virtual void Serialize(POPBuffer &buf, bool pack);

};

#endif
