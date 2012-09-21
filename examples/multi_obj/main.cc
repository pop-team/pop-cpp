#include "myobj1.ph"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{

	try {

		MyObj1 o1("localhost");
		o1.Set(0);

		cout << "Result : " << o1.Get() << endl;
	}
	catch (POPException *e)
	{
		cout<<"Exception occurs in application..."<<endl;
		e->Print();
		return -1;
	}
	catch (...)
	{
		cout<<"Unknown exception occurs in application..."<<endl;
		return -1;

	}
	cout << "it's finished ... " << endl;
	return 0;

}
