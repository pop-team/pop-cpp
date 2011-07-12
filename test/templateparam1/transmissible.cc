#include "transmissible.h"
#include "X.h"
#include "ClassA.cc"

Transmissible::Transmissible() {;}
Transmissible::~Transmissible() {;}
void Transmissible::Serialize(POPBuffer &buf, bool pack)
{
	GetData()->Serialize(buf, pack);
}




