/**
 * File : popfile_datathread.cc
 * Author : Valentin Clement
 * Description : 
 * Creation date : 2012/04/06
 * 
 * Modifications : 
 * Authors		Date			Comment
 * clementval	2012/04/06  Creation of this file
 */

#include "popfile_datathread.h"

#include <pthread.h>

using namespace popfile;


POPFileDataThread::POPFileDataThread(int workersnb)
{
	pthread_t workers[workersnb];
//	for (int i=0; i < workersnb; i++)
//		pthread_create(&workers[i], NULL, Read)
}


void POPFileDataThread::read(){
	
}

void POPFileDataThread::write(){

}



POPFileDataThread::~POPFileDataThread()
{
	
}