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

/**
 * @author Valentin Clement
 * @desc Implementation of small thread that allow the resource discovery algorithm to be unlocked after a timeout
 */

/**
 * NodeThread constructor
 * @param timeout	Time in seconds before unlocking
 * @param node		The POPCSearchNode associated with this thread
 * @param reqid	The request identifier associated with this thread
 */
NodeThread::NodeThread(int timeout, const paroc_accesspoint &node, std::string reqid) : 
	_timeout(timeout), _node(node), _running(true), _unlock(true), _reqid(reqid), paroc_thread(true) {}
	
/** 
 * Start a timer and contact de POPCSearchNode when it's finished
 */
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
	if(_unlock){
		POPString r(_reqid.c_str());
		n.unlockDiscovery(r);
	}
}
/** 
 * Stop the timer and 
 */
void NodeThread::stop(){
	_unlock = false;
	_running = false;
}
