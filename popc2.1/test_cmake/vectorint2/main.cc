#include <stdio.h>
#include "ParObject.ph"
#include <vector>
#include "popintvector.h"

using namespace std;

int main(int argc, char** argv)
{

	printf("\nVectorInt2: Starting test..\n");

	int v;
	POPintVector b;
	ParObject o("localhost");

	for (int i=0; i<10; i++) b.push_back(i);
	b.SetMyData(100);
	o.SetData(b);

	o.GetData().ShowPOPintVector();
	for (int i=0; i<20; i++) b.push_back(20-i);
	b.SetMyData(200);
	o.SetData(b);
	o.GetData().ShowPOPintVector();

	v = o.GetData().size();
	printf("VectorInt2: Current vector size =%d\n", v);
	printf("VectorInt2: My current data =%d\n", o.GetData().GetMyData());

	if (v==30) printf("VectorInt2: test succeeded, destroying objects...\n");
	else printf("VectorInt2: Test failed, bad value transmission\n");

	return 0;
}

