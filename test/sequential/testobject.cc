#include "testobject.ph"


TestObject::TestObject(POPString address) {
    printf("TestObject created\n");
}

TestObject::~TestObject() {
    printf("TestObject destroyed\n");
}

void TestObject::syncConcMethod(POPString label, int waitingTime) {
    printf("Concurrent method (%s) starts\n", label.c_str());
    usleep(waitingTime);
    printf("Concurrent method (%s) ends (execution time %d ns)\n", label.c_str(), waitingTime);
}

void TestObject::syncSeqMethod(POPString label, int waitingTime) {
    printf("Sequential method (%s) starts\n", label.c_str());
    usleep(waitingTime);
    printf("Sequential method (%s) ends (execution time %d ns)\n", label.c_str(), waitingTime);
}

void TestObject::syncMutexMethod(POPString label, int waitingTime) {
    printf("Mutex method (%s) starts\n", label.c_str());
    usleep(waitingTime);
    printf("Mutex method (%s) ends (execution time %d ns)\n", label.c_str(), waitingTime);
}

void TestObject::asyncConcMethod(POPString label, int waitingTime) {
    printf("Concurrent method (%s) starts\n", label.c_str());
    usleep(waitingTime);
    printf("Concurrent method (%s) ends (execution time %d ns)\n", label.c_str(), waitingTime);
}

void TestObject::asyncSeqMethod(POPString label, int waitingTime) {
    printf("Sequential method (%s) starts\n", label.c_str());
    usleep(waitingTime);
    printf("Sequential method (%s) ends (execution time %d ns)\n", label.c_str(), waitingTime);
}

void TestObject::asyncMutexMethod(POPString label, int waitingTime) {
    printf("Mutex method (%s) starts\n", label.c_str());
    usleep(waitingTime);
    printf("Mutex method (%s) ends (execution time %d ns)\n", label.c_str(), waitingTime);
}

@pack(TestObject);
