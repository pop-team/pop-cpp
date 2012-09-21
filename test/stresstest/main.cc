#include "POPObject.ph"

/** 
 * @author  clementval
 * @date    2012.08.22
 * This program tests asynchronous parallel object allocation
 */
int main(int argc, char** argv)
{
	try {
		printf("Stress test: Starting test...\n");
		POPObject o1;
		for (int i=0; i<10000; i++)
			o1.increment();
		
		int value = o1.getCounter();
		if(value == 10000)
			printf("Stress test: test succeeded, destroying objects ...\n");
		else 
			printf("Stress failed: test succeeded, destroying objects ...\n");
	} catch (POPException e) {
		printf("Stress test failed: error no.%d, destroying objects:\n", e.Code());
	}
	return 0;
}
