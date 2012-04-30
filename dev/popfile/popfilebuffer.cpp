#include "popfilebuffer.h"
#include "popfilemanager.ph"
#include "paroc_thread.h"
#include <sys/time.h>
#include <unistd.h>
//#include <semaphor.h>


using namespace popfile;

/*
class POPFileBufferThread: public paroc_thread
{
public:
	POPFileBufferThread(sem_t* lock, POPFileBuffer* buf);
	virtual void start();
private:
	sem_t *locker;
	POPFileBuffer* buffer; 
};

POPFileBufferThread::POPFileBufferThread(sem_t* lock, POPFileBuffer* buf): paroc_thread(true)
{
	locker = lock;
}

void POPFileBufferThread::start()
{
	while (1)
	{
		//Do something
	}
}
*/


POPFileBuffer::POPFileBuffer(){
	capacity = 1024;
	remainingCapacity = capacity;
	identifier = 0;
}
POPFileBuffer::~POPFileBuffer(){
	delete pfmref;
}

/**
 * add string value to the buffer and manage flushing mechanism
 * @param value 
 * @return remaining
 */
std::string POPFileBuffer::buffer_add(std::string value){
	std::string remaining;
	if(value.length() < remainingCapacity){
		popfile_buffer << value;	
		remainingCapacity -= value.length();
	} else {
		remaining = value.substr(remainingCapacity);
		std::string toadd = value.substr(0, remainingCapacity);
		remainingCapacity -= toadd.length();
		popfile_buffer << toadd;	
		flush();
	}
	return remaining;
}

void POPFileBuffer::flush(){
	if(remainingCapacity < capacity){
		struct timeval start1, end1, start2, end2, start3, end3;
	   long mtime, seconds, useconds; 

//		POPFileManager pfm(associatedPFM);
		gettimeofday(&start1, NULL);	
		POPString data(popfile_buffer.str().c_str());
		localpfmref->writeToRemoteStrip(stripPath, data, associatedPFM);
		gettimeofday(&end1, NULL);		
		seconds  = end1.tv_sec  - start1.tv_sec;
   	useconds = end1.tv_usec - start1.tv_usec;
	   mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
		
	//	pfmref->writeToStrip(stripPath, data);
	//	cout << "[POPFILEBUFFER] Flushing buffer[" << identifier << "] "<< remainingCapacity  <<"/" << popfile_buffer.str().length() << ":" << mtime << popcendl;
		
		
		
		/*gettimeofday(&start2, NULL);			
		pfmref->writeToStrip(stripPath, data);	
		gettimeofday(&end2, NULL);
	   seconds  = end2.tv_sec  - start2.tv_sec;
   	useconds = end2.tv_usec - start2.tv_usec;
	   mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
		cout << "[POPFILEBUFFER] async call without parameter [" << identifier << "] time:" << mtime << popcendl;
		
		
		gettimeofday(&start3, NULL);			
		pfmref->writeToStrip(stripPath, data);
		gettimeofday(&end3, NULL);
	   seconds  = end3.tv_sec  - start3.tv_sec;
   	useconds = end3.tv_usec - start3.tv_usec;
	   mtime = ((seconds) * 1000 + useconds/1000.0) + 0.5;
		cout << "[POPFILEBUFFER] async call with parameter [" << identifier << "] time:" << mtime << popcendl;		*/
		
		
		popfile_buffer.str("");
		remainingCapacity = capacity;		
	}
}

void POPFileBuffer::setCapacity(long value)
{
	capacity = value;	
	remainingCapacity = capacity;	
}
void POPFileBuffer::setIdentifier(int value)
{
	identifier = value;
}
void POPFileBuffer::setStripPath(std::string value)
{
	stripPath = value.c_str();
}
void POPFileBuffer::setAssociatedPOPFileManager(paroc_accesspoint ap)
{
	associatedPFM = ap;
	pfmref = new POPFileManager(associatedPFM);
}

void POPFileBuffer::setLocalPOPFileManager(paroc_accesspoint ap)
{
	localpfmref = new POPFileManager(ap);
}


/*
std::stringstream & operator<< (std::stringstream &out, std::string &t)
{
    out << t.str();
    return out;
}

*/