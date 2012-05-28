/**
 * File: main.cpp
 * Author: Valentin Clement
 * Description: Test application for the POPFile library. This application allows to tests various features of the POPFile library. 
 * Creation date: 03.25.2012
 * 
 * Change Log: 
 * Author		Date			Description
 * clementval	03.25.2012	Creation of this file
 */
 
#include "popfile.h"
#include "popfile_grip.h"
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>

#define FILEPATH "myFirstPOPFile"
#define FILE2 "hugefile"
// 1024 = 1MB strip factor
// 5120 = 5MB Strip factor	   	
// 10240 = 10MB Strip factor
#define STRIP_FACTOR 1024

// 102400 = 100MB
// 204800 = 200MB
// 512000 = 500MB
// 1024000 = 1GB
// 5120000 = 5GB
#define FILE_SIZE 204800

using namespace popfile;

int main(int argc, char** argv)
{
	
	int testcase = 0;
	if(argc < 2){
		cout << "[POPFILETEST] Please provide a test case identifier:" << popcendl;
		cout << "[POPFILETEST] 1. Test creation and writing process" << popcendl;
		cout << "[POPFILETEST] 2. Test opening and write to end of file" << popcendl;		
		cout << "[POPFILETEST] 3. Test opening and reading process (background)" << popcendl;
		cout << "[POPFILETEST] 4. Test opening and reading process" << popcendl;	
		cout << "[POPFILETEST] 5. Test opening of a standard file and scatter" << popcendl;	
		cout << "[POPFILETEST] 6. Test opening of a parallel file and gather" << popcendl;			
		cout << "[POPFILETEST] 0. Exit this program" << popcendl;					
		cout << "[POPFILETEST] Test case number:" << popcendl;	
		std::cin >> testcase;	
		cout << "[POPFILETEST] Running test case: " << testcase << popcendl;	
	}
		
		
	struct timeval start, end, start2, end2;

   long mtime, seconds, useconds;  
	POPFStream pfstream;
	if(testcase < 0 || testcase > 6){
		cout << "[POPFILETEST] Test case must be an integer between 0 and 6 !" << popcendl;	
		return -1;	
	}
	
	
   switch(testcase){
   	case 0:
   		cout << "Exiting the program..." << popcendl;
			break;
   	case 1: {
	   	gettimeofday(&start, NULL);	

			pfstream.open(FILE2, 4, STRIP_FACTOR, true);

			for (int i = 0; i < FILE_SIZE; i++){
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
   		sleep(20);
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
			pfstream.open(FILE2, 4, STRIP_FACTOR, true);
			POPFileGrip grip = pfstream.read_in_background(25000000);			
			std::string data = pfstream.get_read(grip);
			cout << data.substr(2048, 2048) << popcendl;
			POPFileGrip grip2 = pfstream.read_in_background(25000000);
			std::string data2 = pfstream.get_read(grip2);			
			POPFileGrip grip3 = pfstream.read_in_background(25000000);
			std::string data3 = pfstream.get_read(grip3);						
			gettimeofday(&end, NULL);
			pfstream.close();
			seconds  = end.tv_sec  - start.tv_sec;
			useconds = end.tv_usec - start.tv_usec;
			mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;			
   		cout << "[POPFILETEST] Reading time : [ms]" << mtime << popcendl;		  			
   		}
   		break;	
  		case 4: {
   		gettimeofday(&start, NULL);	
			pfstream.open(FILE2, 4, STRIP_FACTOR, true);
			long size = FILE_SIZE;
			std::string data = pfstream.read(FILE_SIZE*256);		
			gettimeofday(&end, NULL);
			pfstream.close();
			seconds  = end.tv_sec  - start.tv_sec;
			useconds = end.tv_usec - start.tv_usec;
			mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;			
   		cout << "[POPFILETEST] Reading time : [ms]" << mtime << popcendl;		   			
   		}
   		break;
   	case 5: {
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
		case 6: {
	   		pfstream.open(FILE2, 4, STRIP_FACTOR, true);
	   		if(pfstream.is_open()) {
	   			cout << "[POPFILETEST] File is open" << popcendl;
	   		}
	   		if(pfstream.is_parallel()){
	   			cout << "[POPFILETEST] File is parallel" << popcendl;
	   			pfstream.gather();
	   		} else {
	   			cout << "[POPFILETEST] File is standard" << popcendl;
	   		}
	   		pfstream.close();	   		
   		}
	   	break;
	   	
	   default:
	   	cout << "[POPFILETEST] No test case selected. Abort !" << popcendl;
   		return -1;	   	
	   	break;	
   }

	cout << "[POPFILETEST] End of POPFile prototype test program" << popcendl;
	return 0;	
}


