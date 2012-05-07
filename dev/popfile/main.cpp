#include "popfile.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

#define FILEPATH "myFirstPOPFile"
#define FILE2 "hugefile"

using namespace popfile;

int main(int argc, char** argv)
{
	struct timeval start, end, start2, end2;

   long mtime, seconds, useconds;  
	
	cout << "[POPFILE] Start of POPFile prototype test program:" << popcendl;


   gettimeofday(&start, NULL);	
	
	POPFStream pfstream; // Declare and open a file
	
	pfstream.open(FILE2, 4, 10000000);
	
	for (int i = 0; i < 102400; i++){
		pfstream.write("start1024___");
		pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
		pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
		pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
		pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
		pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
		pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
		pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
		pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
		pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");
		pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");														pfstream.write("stop_1024___");		
	}		
	
	gettimeofday(&end, NULL);
	

	
	gettimeofday(&start2, NULL);
	
	sleep(4);
	
	pfstream.read_in_background();
	sleep(4);
	
	std::string data = pfstream.get_read();
	cout << data.substr(2048, 2048) << popcendl;
	
	gettimeofday(&end2, NULL);
	
	pfstream.close();

   

   seconds  = end.tv_sec  - start.tv_sec;
   useconds = end.tv_usec - start.tv_usec;

   mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
   
   

	
	/*if(pfstream.is_parallel()){
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
	}*/
	cout << "[POPFILE] Writing time : [ms]" << mtime << popcendl;
	cout << "[POPFILE] End of POPFile prototype test program" << popcendl;
}
