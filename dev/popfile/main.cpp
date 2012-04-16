#include "popfile.h"

#define FILEPATH "myFirstPOPFile"

using namespace popfile;

int main(int argc, char** argv)
{
	cout << "[POPFILE] Start of POPFile prototype test program:" << popcendl;
	
	POPFStream pfstream(FILEPATH); // Declare and open a file
	if(pfstream.is_parallel()){
		cout << "[POPFILE] " << FILEPATH << " %s is a parallel file" << popcendl;
		if(pfstream.is_open()){
			cout << "[POPFILE] " << FILEPATH << " is open" << popcendl;
			infos_t info;
			pfstream.get_infos(&info);
			cout << "[POPFILE] The parallel file has " << info.nb_strips << " strips" << popcendl;
			cout << "[POPFILE] The parallel file has " << info.offset << " for offset" << popcendl;
			pfstream.close();
		} else {
			cout << "[POPFILE] " << FILEPATH << " is closed" << popcendl;
		}
	} else {
		cout << "[POPFILE] " << FILEPATH << " is NOT a parallel file" << popcendl;
		if(pfstream.is_open()){
			cout << "[POPFILE] " << FILEPATH << " is open" << popcendl;
		} else {
			cout << "[POPFILE] " << FILEPATH << " is closed" << popcendl;		
		}	
	}
	
	cout << "[POPFILE] End of POPFile prototype test program:" << popcendl;
}
