#include "popfile.h"

#define FILEPATH "myFirstPOPFile"

using namespace popfile;

int main( int argc, const char* argv[] )
{
	printf("Start of POPFile prototype test program: \n");
	
	POPStream pstream(FILEPATH); // Declare and open a file
	if(pstream.is_parallel()){
		printf("%s is a parallel file \n", FILEPATH);
		if(pstream.is_open()){
			printf("%s is open\n", FILEPATH);	
			infos_t info;
			pstream.get_infos(&info);
			printf("The parallel file has %d strips\n", info.nb_strips);
			
			
			pstream.close();
		} else {
			printf("%s is closed\n", FILEPATH);		
		}
	} else {
		printf("%s is NOT a parallel file \n", FILEPATH);
		if(pstream.is_open()){
			printf("%s is open\n", FILEPATH);	
		} else {
			printf("%s is closed\n", FILEPATH);		
		}	
	}
	
	printf("... End of POPFile prototype test program: \n");	
}
