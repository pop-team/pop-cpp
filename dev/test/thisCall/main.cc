#include "POPObject.ph"

/**
 * @author  clementval
 * @date    2011.11.28
 * This program is testing the different calling configuration using the keyword this.
 */
int main(int argc, char** argv)

{
    POPObject o;

    /* Call from a synchornous concurrent method to other semantics methods using "this"
     * Only the call to a synchronous mutex method is forbidden.
     * The call to an asnychronous mutex method is note recommended because it will work only in some cases.
     */
    o.fromSyncConc(SYNCSEQ);
    o.fromSyncConc(SYNCCONC);
    o.fromSyncConc(SYNCMUTEX);
    o.fromSyncConc(ASYNCSEQ);
    o.fromSyncConc(ASYNCCONC);
    o.fromSyncConc(ASYNCMUTEX);

    sleep(1);  // Time to finish previous execution

    /* Call from a synchronous sequential method to other semantics methods using "this"
     * The calls to a synchronous sequential and a synchronous mutex method are fodbidden.
     * The call to an asnychronous mutex method is note recommended because it will work only in some cases.
     */
    o.fromSyncSeq(SYNCSEQ);
    o.fromSyncSeq(SYNCCONC);
    o.fromSyncSeq(SYNCMUTEX);
    o.fromSyncSeq(ASYNCSEQ);
    o.fromSyncSeq(ASYNCCONC);
    o.fromSyncSeq(ASYNCMUTEX);

    sleep(1);  // Time to finish previous execution

    /* Call from a synchronous sequential method to other semantics methods using "this"
     * The calls to any synchronous method are fodbidden.
     * The call to an asnychronous mutex method is note recommended because it will work only in some cases.
     */
    o.fromSyncMutex(SYNCSEQ);
    o.fromSyncMutex(SYNCCONC);
    o.fromSyncMutex(SYNCMUTEX);
    o.fromSyncMutex(ASYNCSEQ);
    o.fromSyncMutex(ASYNCCONC);
    o.fromSyncMutex(ASYNCMUTEX);

    sleep(1);  // Time to finish previous execution

    /* Call from a synchronous sequential method to other semantics methods using "this"
     * The calls to any mutex method are fodbidden.
     * The call to an asnychronous mutex method is note recommended because it will work only in some cases.
     */
    o.fromAsyncConc(SYNCSEQ);
    o.fromAsyncConc(SYNCCONC);
    o.fromAsyncConc(SYNCMUTEX);
    o.fromAsyncConc(ASYNCSEQ);
    o.fromAsyncConc(ASYNCCONC);
    o.fromAsyncConc(ASYNCMUTEX);

    sleep(1);  // Time to finish previous execution

    /* Call from a synchronous sequential method to other semantics methods using "this"
     * The calls to a synchronous sequential and synchronous mutex method are fodbidden.
     * The call to an asnychronous mutex method is note recommended because it will work only in some cases.
     */
    o.fromAsyncSeq(SYNCSEQ);
    o.fromAsyncSeq(SYNCCONC);
    o.fromAsyncSeq(SYNCMUTEX);
    o.fromAsyncSeq(ASYNCSEQ);
    o.fromAsyncSeq(ASYNCCONC);
    o.fromAsyncSeq(ASYNCMUTEX);

    sleep(1);  // Time to finish previous execution

    /* Call from a synchronous sequential method to other semantics methods using "this"
     * The calls to any synchronous method are fodbidden.
     * The call to an asnychronous mutex method is note recommended because it will work only in some cases.
     */
    o.fromAsyncMutex(SYNCSEQ);
    o.fromAsyncMutex(SYNCCONC);
    o.fromAsyncMutex(SYNCMUTEX);
    o.fromAsyncMutex(ASYNCSEQ);
    o.fromAsyncMutex(ASYNCCONC);
    o.fromAsyncMutex(ASYNCMUTEX);

    sleep(1);  // Time to finish previous execution

    cout << "Calling method using this, TEST SUCCESSFUL" << popcendl;
    cout << popcendl;
    cout << popcendl;
    cout << "##########################################" << popcendl;
    cout << "Accepted call chart:" << popcendl;
    cout << "-->            |sync conc   |sync seq |sync mutex  |async conc  |async seq   |async mutex     |"
         << popcendl;
    cout << "---------------|------------|---------|------------|------------|------------|----------------|"
         << popcendl;
    cout << "sync conc      |OK          |OK       |FREEZE      |OK          |OK          |NOT RECOMMENDED |"
         << popcendl;
    cout << "---------------|------------|---------|------------|------------|------------|----------------|"
         << popcendl;
    cout << "sync seq       |OK          |FREEZE   |FREEZE      |OK          |OK          |NOT RECOMMENDED |"
         << popcendl;
    cout << "---------------|------------|---------|------------|------------|------------|----------------|"
         << popcendl;
    cout << "sync mutex     |FREEZE      |FREEZE   |FREEZE      |OK          |OK          |NOT RECOMMENDED |"
         << popcendl;
    cout << "---------------|------------|---------|------------|------------|------------|----------------|"
         << popcendl;
    cout << "async conc     |OK          |OK       |FREEZE      |OK          |OK          |NOT RECOMMENDED |"
         << popcendl;
    cout << "---------------|------------|---------|------------|------------|------------|----------------|"
         << popcendl;
    cout << "async seq      |OK          |FREEZE   |FREEZE      |OK          |OK          |NOT RECOMMENDED |"
         << popcendl;
    cout << "---------------|------------|---------|------------|------------|------------|----------------|"
         << popcendl;
    cout << "async mutex    |FREEZE      |FREEZE   |FREEZE      |OK          |OK          |NOT RECOMMENDED |"
         << popcendl;
    cout << "---------------|------------|---------|------------|------------|------------|----------------|"
         << popcendl;
    cout << popcendl;
    cout << "Note:" << popcendl;
    cout << "- NOT RECOMMENDED means that the execution could work in some cases but not in any cases! So be aware "
            "when you are using these configurations." << popcendl;
    cout << "- FREEZE means that the execution will not work in any cases! Do not use these configurations in a "
            "POP-C++ application." << popcendl;
    cout << "- OK means that the execution will work in any cases! You can use these configurations in a POP-C++ "
            "application." << popcendl;
    return 0;
}
