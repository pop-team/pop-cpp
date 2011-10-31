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
	cout << endl << "Heritage: Starting test..." << endl;
	cout << "Heritage: Creation de Mother c" << endl;
	Mother c;

	cout << "Heritage: Creation de Child c1" << endl;
	Child c1;

	cout << "Heritage: Appel avec Mother, c"<< endl;
	callMethod(c,1);

	cout << "Heritage: Appel avec Child, c1"<<  endl;
	callMethod(c1,2);

	cout <<  endl << "Heritage: Appel callMethod de Mother avec Child, c1"<<  endl;
	c.callMethod(c1,3);

	cout <<  endl<< "Heritage: Appel callMethod de Child avec Mother, c"<<  endl;
	c1.callMethod(c,4);

	//cout <<  endl << "Appel callMethod de Child avec Child, c1"<<  endl;
	//c1.callMethod(c1,5);

	//cout <<  endl << "Heritage: Appel callMethod de Mother avec Mother, c"<<  endl;
	//c.callMethod(c,6);
	cout << "Heritage: test succeeded, destroying objects..." << endl;
	return 0;

}



