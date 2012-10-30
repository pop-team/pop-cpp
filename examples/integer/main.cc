#include "integer.ph"
#include <iostream>
#include <assert.h>

using namespace std;

int main(int argc, char* argv[])
{
	int node = atoi(argv[1]);
	try {
		// Create 2 Integer objects
		Integer o1;
		o1.Set(10);
		printf("o1=%d\n", o1.Get());
		Integer o2;
		o2.Set(11);
		printf("o2=%d\n", o2.Get());
		o1.Add(o2);
		int result = o1.Get();
		cout << "o1=o1+o2; o1=" << result << endl;
		printf("End of test\n");
		assert(result == 21);
	} catch (POPException *e) {
		cout << "Exception occurs in application :" << endl;
		e->Print();
		delete e;
		return -1;
	}
	printf("Integer test ended\n");
	return 0;
}
