#include <stdio.h>
#include <vector>

#include "ParObject.ph"
#include "popxvector.h"
#include "X.h"

int main(int argc, char** argv)
{
	printf("\nVectorX: Starting test..\n");

	X v;
	POPxVector b;
	vector<X>::iterator iter;
	ParObject o("localhost");

	for (int i=0; i<10; i++) {v.SetValue(i); b.push_back(v);}
	o.SetData(b);
	b.clear();
	b = o.GetData();

	printf("VectorX: Vector is of size %d: ", b.size());
	for (iter=b.begin(); iter!=b.end(); iter++)
		printf("%d ",iter->GetValue()); printf("\n");

	b.clear();
	for (int i=0; i<20; i++) {v.SetValue(20-i); b.push_back(v);}
	o.SetData(b);
	b.clear();
	b = o.GetData();

	printf("VectorX: Vector is of size %d: ", b.size());
	for (iter=b.begin(); iter!=b.end(); iter++)
		printf("%d ",iter->GetValue()); printf("\n");

	printf("VectorX: Current vector size =%d\n", b.size());

	if (b.size()==20) printf("VectorX: test succeeded, destroying objects...\n");
	else printf("VectorX: Test failed, bad value transmission\n");

	return 0;
}

