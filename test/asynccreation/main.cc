#include "POPObject.ph"

/** 
 * @author  clementval
 * @date    2012.07.11
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */
int main(int argc, char** argv)
{
	try {
		printf("Asynchronous allocation of parallel object\n");
		printf("Before creating POPObject o1\n");
		POPObject o1;
		printf("Before creating POPObject o2\n");
		POPObject o2;
		printf("Before creating POPObject o3\n");		
		POPObject o3;
		printf("Before calling method 1 on POPObject o1\n");		
		o1.firstMethod();
		printf("Before calling method 1 on POPObject o2\n");		
		o2.firstMethod();
		printf("Before calling method 1 on POPObject o3\n");		
		o3.firstMethod();		
		printf("Before calling method 2 on POPObject o1\n");		
		o1.secondMethod();		
		printf("Before calling method 2 on POPObject o2\n");		
		o2.secondMethod();		
		printf("Before calling method 2 on POPObject o3\n");		
		o3.secondMethod();						
		printf("Method with void parameter: test succeeded, destroying objects ...\n");
	} catch (POPException e) {
		printf("Method with void parameter: test failed, error no.%d, destroying objects:\n", e.Code());
	}
	return 0;
}
