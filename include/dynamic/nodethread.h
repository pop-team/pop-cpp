#include "paroc_thread.h"

#include <string.h>

class NodeThread : public paroc_thread {
public:
	NodeThread(int timeout, const paroc_accesspoint &node, std::string reqid);
	virtual void start();
	virtual void stop();
private:
	std::string _reqid;
	int _timeout;
	bool _running;
	bool _unlock;
	paroc_accesspoint _node;
};
