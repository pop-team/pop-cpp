#include "POPObject.ph"
#include "POPData.h"

/** 
 * @author  clementval
 * @date    2011.11.28
 * This program is testing various known bug in POP-C++
 */
int main(int argc, char** argv)
{
	cout << "Showing problem number 17 - Passing array of POPBase inherited objects" << popcendl;
	POPObject o;
	
	POPData d;
	d.setIntData(10);
	
	int n = 10;
	POPData data[n];
	
	for(int i=0; i<n; i++)
		data[i].setIntData(i);
	
	o.transferPOPBaseArray(n, data);
	o.transferPOPBaseData(d);
	
	return 0;
}
