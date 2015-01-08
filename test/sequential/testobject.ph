#ifndef TEST_OBJECT_PH
#define TEST_OBJECT_PH

#include <timer.h>

parclass TestObject {
    classuid(1500);

public:
    TestObject(POPString address); // @{ od.url(address); };
    ~TestObject();

    sync conc void syncConcMethod(POPString label, int waitingTime);
    sync seq void syncSeqMethod(POPString label, int waitingTime);
    sync mutex void syncMutexMethod(POPString label, int waitingTime);
    async conc void asyncConcMethod(POPString label, int waitingTime);
    async seq void asyncSeqMethod(POPString label, int waitingTime);
    async mutex void asyncMutexMethod(POPString label, int waitingTime);

private:
};

#endif /*TEST_OBJECT_PH*/
