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
	
	cout << "[POPFILE] Start of standard test program:" << endl;
   
	ofstream pfstream; // Declare and open a file
	pfstream.open("testfile");
	// 102400 = 100MB
	// 204800 = 200MB
	// 512000 = 500MB
	// 1024000 = 1GB
	// 5120000 = 5GB
	for (int i = 0; i < 512000; i++){
		pfstream << "start1024_//";
		pfstream << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		pfstream << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		pfstream << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		pfstream << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		pfstream << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		pfstream << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		pfstream << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		pfstream << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		pfstream << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";
		pfstream << "0123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789";															
		pfstream << "stop_1024_//";	
	}		
	

	pfstream.close();
   
/*
	   
   int length=0;
   gettimeofday(&start, NULL);	
	ifstream strip;
	strip.open("testfile", ios::binary);
	
	strip.seekg (0, ios::end);		// Seek to end
	length = strip.tellg();			// Get length of the strip
	cout << "[POPFILE] Length:" << length << endl;
	strip.seekg (0, ios::beg);


	char* buffer;
	buffer = new char[(length/2)+1];
	
	strip.read(buffer, (length/2));	
	strip.read(buffer, (length/2));	
	
	
	
	strip.close();
	gettimeofday(&end, NULL);


   seconds  = end.tv_sec  - start.tv_sec;
   useconds = end.tv_usec - start.tv_usec;
 
   mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
	
	cout << "[POPFILE] End of POPFile prototype test program: [ms]" << mtime << endl;
	
	*/
}
