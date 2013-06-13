#include "POPObject.ph"

/** 
 * @author  clementval
 * @date    2012.07.11
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */
int main(int argc, char** argv)
{
	try {
		printf("Method with void parameter: Starting test...\n");
		POPObject o;
		o.voidMethod(o);
		printf("Method with void parameter: test succeeded, destroying objects ...\n");
	} catch (POPException e) {
		printf("Method with void parameter: test failed, error no.%d, destroying objects:\n", e.Code()); return 1;
	}
	return 0;
}
