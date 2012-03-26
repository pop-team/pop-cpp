#include <stdio.h>
#include "ParObject.ph"
#include <vector>
#include "popintvector.h"

using namespace std;

int main(int argc, char** argv)
{

	printf("\nVectorInt1: Starting test..\n");

	int v;
	POPintVector b, c;
	ParObject o("localhost");
	vector<int> x(10);
	for (int i=0; i<x.size(); i++) x[i]=i;

	b.SetInternalData(x);
	b.SetMyData(100);
	o.SetData(b);

	o.GetData().ShowPOPintVector();

	vector<int> y(20);
	for (int i=0; i<y.size(); i++) y[i]=y.size()-i;
	b.SetInternalData(y);
	b.SetMyData(200);
	o.SetData(b);
	o.GetData().ShowPOPintVector();

	v = o.GetData().GetInternalData().size();
	printf("VectorInt1: Current vector size =%d\n", v);
	printf("VectorInt1: My current data =%d\n", o.GetData().GetMyData());

	if (v==20) printf("VectorInt1: test succeeded, destroying objects...\n");
	else printf("VectorInt1: Test failed, bad value transmission\n");

	return 0;
}

