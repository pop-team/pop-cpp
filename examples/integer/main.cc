


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
		o2.Set(10);
		printf("o2 value is %d\n", o2.Get());
		printf("o1 accesspoint %s\n", o1.GetAccessPoint().GetAccessString());
		printf("o2 accesspoint %s\n", o2.GetAccessPoint().GetAccessString());		
		
		o1.Add(o2);
		printf("get result of add\n");		
		printf("o1 new value is %d\n", o1.Get());		
		printf("End of program\n");
	} catch (POPException *e) {
		cout << "Exception occurs in application :" << endl;
		e->Print();
		delete e;
		return -1;
	}
	return 0;
}
