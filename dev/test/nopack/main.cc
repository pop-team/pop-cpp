#include "POPObject.ph"

/** 
 * @author  clementval
 * @date    2012.07.11
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */
int main(int argc, char** argv)

{
	POPObject o;
	printf("NoPack: test succeeded, destroying objects..\n");
	return 0;
}
