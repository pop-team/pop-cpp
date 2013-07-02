#include "POPObject.ph"

/** 
 * @author  clementval
 * @date    2012.07.11
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */
int main(int argc, char** argv)

{
  	//std::cout << "Standard syntax array: Starting test..." << std::endl;
	printf("Standard syntax array: Starting test...\n");
	int ele;
	
	ele = 10;		
	printf("POPObject will be created\n");//vanhieu.nguyen
	POPObject o;
        printf("POPObject has been created\n");//vanhieu.nguyen
	o.displayEle(ele);

	//std::cout << "Return of parallel object" << std::endl;	
	printf("Return of parallel object\n");
        //std::cout << "item[" << i << "]=" << array[i] << std::endl;
        printf("ele=%d\n", ele);
	
	//std::cout << "Standard syntax array: test succeeded, destroying object..." << std::endl;		
	printf("Standard syntax array: test succeeded, destroying object...\n");
	return 0;
}
