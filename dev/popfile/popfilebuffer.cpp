#include "popfilebuffer.h"
#include "popfilemanager.ph"
#include "paroc_thread.h"
#include <semaphor.h>


using namespace popfile;

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



POPFileBuffer::POPFileBuffer(){
	capacity = 1024;
	remainingCapacity = capacity;
	identifier = 0;
}
POPFileBuffer::~POPFileBuffer(){
	
}

std::string POPFileBuffer::buffer_add(std::string value){
	std::string remaining;
	if(value.length() < remainingCapacity){
		popfile_buffer << value;	
		remainingCapacity -= value.length();
//		cout << "[POPFILEBUFFER] Write in buffer (" << identifier << ") / remaining ("<< remainingCapacity <<")" << value << popcendl; 			
	} else {
 			
		remaining = value.substr(remainingCapacity);
		std::string toadd = value.substr(0, remainingCapacity);
		popfile_buffer << toadd;	
//		cout << "[POPFILEBUFFER] Value is too long (" << value.length() << ") / remaining ("<< remaining <<")" << toadd << popcendl;
		flush();
	}

	return remaining;
}

void POPFileBuffer::flush(){
	if(remainingCapacity < capacity){
		POPFileManager pfm(associatedPFM);
		POPString data(popfile_buffer.str().c_str());
//		pfmref->writeToStrip(stripPath, data);
		pfm.writeToStrip(stripPath, data);
		//cout << "[POPFILEBUFFER] Flushing buffer[" << identifier << "]" << popcendl;
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
	//pfmref = new POPFileManager(associatedPFM);
}



/*
std::stringstream & operator<< (std::stringstream &out, std::string &t)
{
    out << t.str();
    return out;
}

*/