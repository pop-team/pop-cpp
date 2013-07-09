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
     	/*printf("Standard syntax array: Starting test...\n");

	int array[5];
	
	array[0] = 10;
	array[1] = 20;
	array[2] = 30;
	array[3] = 40;	
	array[4] = 50;		
	
	POPObject o;
	o.displayArray(5, array);

	printf("Return of parallel object\n");        
	for(int i=0; i<5; i++){
		printf("item[%d]=%d\n", i, array[i]);
	}
	
	printf("Standard syntax array: test succeeded, destroying object...\n");	
	return 0;*/
}
