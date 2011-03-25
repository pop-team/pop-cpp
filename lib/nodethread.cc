/**
 * File : nodethread.cc
 * Author : Valentin Clement (clementval)
 * Description : Implementation of a small timer to unlock the resource discovery when used with timeout 0
 * Creation date : 05/2010
 * 
 * Modifications :
 * Authors		Date			Comment
 */

#include "nodethread.h"
#include "popc_search_node.ph"

//Implementation of this small class
NodeThread::NodeThread(int timeout, const paroc_accesspoint &node) : paroc_thread(true) {
	_timeout = timeout;
	_node = node;
	_running = true;
	_unlock = true;
}
//Start a timer and contact de POPCSearchNode when it's finished
void NodeThread::start(){
	POPCSearchNode n(_node);
	Timer t;
	t.Start();
	while(_running){
		usleep(100000);
		if(t.Elapsed() > _timeout){
			t.Stop();
			_running = false;
		}
	}
	if(_unlock)
		n.unlockDiscovery();
}
//Stop the timer
void NodeThread::stop(){
	_unlock = false;
	_running = false;
}
