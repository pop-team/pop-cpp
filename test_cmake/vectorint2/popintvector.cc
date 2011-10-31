#include <stdio.h>
#include "popintvector.h"

POPintVector::POPintVector() {}

POPintVector::~POPintVector() {};

void POPintVector::ShowPOPintVector()
{
	printf("VectorInt2: Vector is of size %d: ", size());
	vector<int>::iterator iter;
	for (iter=begin(); iter!=end(); iter++)
		printf("%d ",*iter);
	printf("\nVectorInt2: MyData = %d\n", myData);
}

void POPintVector::SetMyData(int d) {myData = d;}

int POPintVector::GetMyData() {return myData;}

void POPintVector::Serialize(POPBuffer &buf, bool pack)
{
	int a;
	long vsize;
	vector<int>::iterator iter;
	if (pack)
	{
		vsize=size();
		buf.Pack(&vsize,1);
		for (iter=begin(); iter!=end(); iter++)
		{
			a = *iter;
			buf.Pack(&a,1);
		}
		buf.Pack(&myData,1);
	}
	else
	{
		buf.UnPack(&vsize,1);
		clear();
		for (long i=0; i<vsize; i++)
		{
			buf.UnPack(&a,1);
			push_back(a);
		}
		buf.UnPack(&myData,1);
	}
}

