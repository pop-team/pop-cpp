#include "POPObject.ph"

/** 
 * @author  clementval
 * @date    2012.08.22
 * This program tests asynchronous parallel object allocation
 */
int main(int argc, char** argv)
{
	try {
		printf("Stress allocationtest started ...\n");
		printf("Number of objects created on your computer can be limited by ulimit\n");
		printf("ulimit -n\t To check how many files can be open on your computer\n");	
		printf("ulimit -n XX\t To change the limit (XX must be a number)\n");
		printf("For this test ulimit will be set to 1024\n");								
		POPObject o[500];
		
	} catch (POPException e) {
		printf("Stress allocation test failed: error no.%d, destroying objects:\n", e.Code());
		return 1;
	}
    printf("Stress allocation test succeeded, destroying objects:\n");
	return 0;
}
