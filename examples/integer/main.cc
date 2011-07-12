#include "integer.ph"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	try
	{
		// Create 3 Integer objects
		Integer o1(60,40);
		Integer o2("localhost");

		// Set values
		o1.Set(1); o2.Set(2);

		cout << endl << "o1="<< o1.Get() << "; o2=" << o2.Get() << endl;

		cout<<"Add o2 to o1"<<endl;
		o1.Add(o2);
		cout << "o1=o1+o2; o1=" << o1.Get() << endl << endl;

	} // Try

	catch (POPException *e)
	{
		cout << "Exception occurs in application :" << endl;
		e->Print();
		delete e;
		return -1;
	} // catch

	return 0;
} //main
