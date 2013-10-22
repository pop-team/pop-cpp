#include "POPObject.ph"

/** 
 * @author  clementval
 * @date    2011.11.28
 * This program is testing the bug number 15 in the known bug list of POP-C++
 */
int main(int argc, char** argv)
{
	cout << "Showing problem number 03 - namespace" << popcendl;
	POPObject o;
	o.dummyMethod();
	return 0;
}
