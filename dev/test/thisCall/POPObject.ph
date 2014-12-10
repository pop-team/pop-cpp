#ifndef POPOBJECT_PH_
#define POPOBJECT_PH_

#define SYNCCONC 0
#define SYNCSEQ 1
#define SYNCMUTEX 2
#define ASYNCCONC 3
#define ASYNCSEQ 4
#define ASYNCMUTEX 5

parclass POPObject {
    classuid(1500);

public:
    POPObject() @{ od.search(0, 0, 0); };
    ~POPObject();

    sync conc void fromSyncConc(int sem);
    sync seq void fromSyncSeq(int sem);
    sync mutex void fromSyncMutex(int sem);
    async conc void fromAsyncConc(int sem);
    async seq void fromAsyncSeq(int sem);
    async mutex void fromAsyncMutex(int sem);

    sync conc void toSyncConc(int callerid);
    sync seq void toSyncSeq(int callerid);
    sync mutex void toSyncMutex(int callerid);
    async conc void toAsyncConc(int callerid);
    async seq void toAsyncSeq(int callerid);
    async mutex void toAsyncMutex(int callerid);
};

#endif /*POPOBJECT_PH_*/
