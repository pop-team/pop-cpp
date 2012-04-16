#include "popfile.h"

#define FILEPATH "myFirstPOPFile"

using namespace popfile;

int main(int argc, char** argv)
{
	cout << "Start of POPFile prototype test program:" << popcendl;
	
	POPFStream pfstream(FILEPATH); // Declare and open a file
	if(pfstream.is_parallel()){
		cout << FILEPATH << "%s is a parallel file" << popcendl;
		if(pfstream.is_open()){
			cout << FILEPATH << " is open" << popcendl;
			infos_t info;
			pfstream.get_infos(&info);
			cout << "The parallel file has " << info.nb_strips << " strips" << popcendl;
			cout << "The parallel file has " << info.offset << " for offset" << popcendl;
			pfstream.close();
		} else {
			cout << FILEPATH << " is closed" << popcendl;
		}
	} else {
		cout << FILEPATH << " is NOT a parallel file" << popcendl;
		if(pfstream.is_open()){
			cout << FILEPATH << " is open" << popcendl;
		} else {
			cout << FILEPATH << " is closed" << popcendl;		
		}	
	}
	
	cout << "… End of POPFile prototype test program:" << popcendl;
}
