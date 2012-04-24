#include <sys/time.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <unistd.h>

using namespace std;

int main(int argc, char** argv)
{
	struct timeval start, end;

   long mtime, seconds, useconds;  
	
	cout << "[POPFILE] Start of POPFile prototype test program:" << endl;


   gettimeofday(&start, NULL);	
	ofstream pfstream; // Declare and open a file
	pfstream.open("testfile");
	
	for (int i = 0; i < 2000000; i++){
		pfstream << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
	}		
	
	pfstream.close();

   gettimeofday(&end, NULL);

   seconds  = end.tv_sec  - start.tv_sec;
   useconds = end.tv_usec - start.tv_usec;
 
   mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
	
	cout << "[POPFILE] End of POPFile prototype test program: [ms]" << mtime << endl;
}
