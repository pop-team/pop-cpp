#include <stdio.h>
#include "popintvector.h"

POPintVector::POPintVector() {}

POPintVector::~POPintVector() {};

void POPintVector::SetInternalData(vector<int> d)
{
	theData = d;
}

void POPintVector::ShowPOPintVector()
{
	printf("VectorInt1: Vector is of size %d: ", theData.size());
	for (long i=0; i<theData.size(); i++) printf("%d ",theData[i]);
	printf("\nVectorInt1: MyData = %d\n", myData);
}

vector<int> POPintVector::GetInternalData() {return theData;}

void POPintVector::SetMyData(int d) {myData = d;}

int POPintVector::GetMyData() {return myData;}

void POPintVector::Serialize(POPBuffer &buf, bool pack)
{
	int a;
	long size;
	vector<int>::iterator iter;
	if (pack)
	{
		size=theData.size();
		buf.Pack(&size,1);
		for (iter=theData.begin(); iter!=theData.end(); iter++)
		{
			a = *iter;
			buf.Pack(&a,1);
		}
		buf.Pack(&myData,1);
	}
	else
	{
		buf.UnPack(&size,1);
		theData.clear();
		for (long i=0; i<size; i++)
		{
			buf.UnPack(&a,1);
			theData.push_back(a);
		}
		buf.UnPack(&myData,1);
	}
}

