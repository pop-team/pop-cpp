#include <stdio.h>
#include "popxvector.h"

POPxVector::POPxVector() {clear();}

POPxVector::~POPxVector() {;}

void POPxVector::Serialize(POPBuffer &buf, bool pack)
{
	long vsize;
	vector<X>::iterator iter;
	if (pack)
	{
		vsize = size();
		buf.Pack(&vsize,1);
	}
	else
	{
		buf.UnPack(&vsize, 1);
		clear();
		resize(vsize);
	}
	for (iter=begin(); iter!=end(); iter++)
		iter->Serialize(buf, pack);
}

