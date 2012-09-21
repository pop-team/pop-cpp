#include "POPObject.ph"

/** 
 * @author  clementval
 * @date    2012.07.11
 * This program tests compilation without the @pack directive. Compilation should work and print a warning message.
 */
int main(int argc, char** argv)

{
  	cout << "Standard syntax array: Starting test..." << popcendl;

	int array[5];
	
	array[0] = 10;
	array[1] = 20;
	array[2] = 30;
	array[3] = 40;	
	array[4] = 50;		
	
	POPObject o;
	o.displayArray(5, array);

	cout << "Return of parallel object" << popcendl;	
	for(int i=0; i<5; i++){
		cout << "item[" << i << "]=" << array[i] << popcendl;
	}
	
	cout << "Standard syntax array: test succeeded, destroying object..." << popcendl;		
	return 0;
}
