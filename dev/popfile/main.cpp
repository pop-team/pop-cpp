#include "popfile.h"
#include "popfile_grip.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

#define FILEPATH "myFirstPOPFile"
#define FILE2 "hugefile"

using namespace popfile;

int main(int argc, char** argv)
{
	
	int testcase = 0;
	if(argc < 2){
		cout << "[POPFILETEST] Please provide a test case identifier:" << popcendl;
		cout << "[POPFILETEST] 1. Test creation and writing process" << popcendl;
		cout << "[POPFILETEST] 2. Test opening and write to end of file" << popcendl;		
		cout << "[POPFILETEST] 3. Test opening and reading process" << popcendl;
		cout << "[POPFILETEST] 4. Test opening of a standard file and scatter" << popcendl;	
		cout << "[POPFILETEST] Test case number:" << popcendl;	
		std::cin >> testcase;	
		cout << "[POPFILETEST] Running test case: " << testcase << popcendl;	
	}
		
		
	struct timeval start, end, start2, end2;

   long mtime, seconds, useconds;  
	POPFStream pfstream;
	
   switch(testcase){
   	case 1: {
	   	gettimeofday(&start, NULL);	
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
				pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");												pfstream.write("stop_1024___");		
			}		
			pfstream.close();			
			gettimeofday(&end, NULL);
			seconds  = end.tv_sec  - start.tv_sec;
			useconds = end.tv_usec - start.tv_usec;
			mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;			
   		cout << "[POPFILETEST] Writing time : [ms]" << mtime << popcendl;
   		}
   		break;
   	case 2: {
   		gettimeofday(&start, NULL);	
			pfstream.open(FILE2);
			for (int i = 0; i < 100; i++){
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
				pfstream.write("0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789");												pfstream.write("stop_1024___");		
			}		
			pfstream.close();			
			gettimeofday(&end, NULL);
			seconds  = end.tv_sec  - start.tv_sec;
			useconds = end.tv_usec - start.tv_usec;
			mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;			
   		cout << "[POPFILETEST] Writing time : [ms]" << mtime << popcendl;
   		}
   		break; 		
   	case 3: {
   		gettimeofday(&start, NULL);	
			pfstream.open(FILE2, 4, 10000000);
			POPFileGrip grip = pfstream.read_in_background(25000000);
			sleep(4);
			std::string data = pfstream.get_read(grip);
			cout << data.substr(2048, 2048) << popcendl;
			gettimeofday(&end, NULL);
			pfstream.close();
			seconds  = end.tv_sec  - start.tv_sec;
			useconds = end.tv_usec - start.tv_usec;
			mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;			
   		cout << "[POPFILETEST] Reading time : [ms]" << mtime << popcendl;			
   		}
   		break;	
   	case 4: {
	   		pfstream.open("testfile");
	   		if(pfstream.is_open()) {
	   			cout << "[POPFILETEST] File is open" << popcendl;
	   		}
	   		if(pfstream.is_parallel()){
	   			cout << "[POPFILETEST] File is parallel" << popcendl;
	   		} else {
	   			cout << "[POPFILETEST] File is standard" << popcendl;
	   		}
	   		pfstream.scatter();
	   		pfstream.close();
   		}
	   	break;
	   default:
	   	cout << "[POPFILETEST] No test case selected. Abort !" << popcendl;
	   	break;	
   }

	cout << "[POPFILETEST] End of POPFile prototype test program" << popcendl;
}


