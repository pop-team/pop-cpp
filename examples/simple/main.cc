


#include "integer.ph"
#include <iostream>

using namespace std;

int main(int argc, char **argv)
{
	try
	{
	  	printf("Starting integer example application\n");
		Integer o1;
		o1.Set(19);

		printf("o1 value is %d\n", o1.Get());
		Integer o2;
		o2.Set(21);
		printf("o2 value is %d\n", o2.Get());
		o1.Add(o2);
		printf("o1+o2=%d\n", o1.Get());
	} catch (POPException *e) {
		cout << "Exception occurs in application :" << endl;
		e->Print();
		delete e;
		return -1;
	}
	printf("end of program\n");
	return 0;
	
}
