#include "popfile.h"

#define FILEPATH "myFirstPOPFile"

using namespace popfile;

int main( int argc, const char* argv[] )
{
	printf("Start of POPFile prototype test program: \n");
	
	POPFStream pfstream(FILEPATH); // Declare and open a file
	if(pfstream.is_parallel()){
		printf("%s is a parallel file \n", FILEPATH);
		if(pfstream.is_open()){
			printf("%s is open\n", FILEPATH);	
			infos_t info;
			pfstream.get_infos(&info);
			printf("The parallel file has %d strips\n", info.nb_strips);
			std::cout << "The parallel file has " << info.offset << " for offset" << std::endl;
			

			pfstream.close();
		} else {
			printf("%s is closed\n", FILEPATH);		
		}
	} else {
		printf("%s is NOT a parallel file \n", FILEPATH);
		if(pfstream.is_open()){
			printf("%s is open\n", FILEPATH);	
		} else {
			printf("%s is closed\n", FILEPATH);		
		}	
	}
	
	printf("... End of POPFile prototype test program: \n");	
}
