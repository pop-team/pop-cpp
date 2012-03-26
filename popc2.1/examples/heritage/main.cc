#include <stdlib.h>
#include <iostream>
#include "mother.ph"
#include "child.ph"

using namespace std;

void callMethod(Mother c, int v)
{
	c.Method1();
	c.SetVal(v);
	c.Method1();
	cout << "Heritage: GetVal="<< c.GetVal() << endl;
}

int main(int argc, char** argv)
{
	cout << endl << "Heritage: Starting..." << endl;

	cout << "Heritage: Creation of object c of class Mother" << endl;
	Mother c;

	cout << "Heritage: Creation of object c1 of class Child" << endl;
	Child c1;

	cout << "Heritage: Call with Mother, c"<< endl;
	callMethod(c,1);

	cout << "Heritage: Call with Child, c1"<<  endl;
	callMethod(c1,2);

	cout << endl << "Heritage: Call callMethod of Mother with Child, c1"<<  endl;
	c.callMethod(c1,3);

	cout <<  endl<< "Heritage: Call callMethod of Child with Mother, c"<<  endl;
	c1.callMethod(c,4);

	cout << "Heritage: Terminated, destroying objects..." << endl;

	return 0;

}
