/**
 * File : popfile_datathread.h
 * Author : Valentin Clement
 * Description : 
 * Creation date : 2012/04/06
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2012/04/06  Creation of this file
 */
 
#ifndef POPFILE_DATATHREAD_H_INCLUDE
#define POPFILE_DATATHREAD_H_INCLUDE


namespace popfile {

class POPFileDataThread {
public:

	// Standard functionalities of stream
	POPFileDataThread(int workersnb);
	~POPFileDataThread();	
	
	void read();
	void write();
	
private:


};	
	
	
} // namespace popfile

#endif
