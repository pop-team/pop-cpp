#include "paroc_thread.h"

class NodeThread : public paroc_thread {
public:
	NodeThread(int timeout, const paroc_accesspoint &node);
	virtual void start();
	virtual void stop();
private:
	int _timeout;
	bool _running;
	bool _unlock;
	paroc_accesspoint _node;
};
