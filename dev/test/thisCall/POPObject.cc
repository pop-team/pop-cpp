#include "POPObject.ph"
#include <unistd.h>

POPObject::POPObject()
{
   cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject()
{
   cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}



/** 
 * Calling any semantics from a synchronous concurrent method
 * @param sem  Semantic to use for the internal call
 */
void POPObject::fromSyncConc(int sem)
{
   if(__POPThis_POPObject != NULL){
      switch(sem){
         case SYNCSEQ:
            cout << "--> (1) Call from sync conc to sync seq" << popcendl;
            (*__POPThis_POPObject).toSyncSeq(1); 
            break;
         case SYNCCONC:
            cout << "--> (1) Call from sync conc to sync conc" << popcendl;
            (*__POPThis_POPObject).toSyncConc(1); 
            break;
         case SYNCMUTEX:           
            cout << "--> (1) Call from sync conc to sync mutex (NOT POSSIBLE)" << popcendl;
            break;
         case ASYNCSEQ:
            cout << "--> (1) Call from sync conc to async seq" << popcendl;
            (*__POPThis_POPObject).toAsyncSeq(1); 
            break;
         case ASYNCCONC:
            cout << "--> (1) Call from sync conc to async conc" << popcendl;
            (*__POPThis_POPObject).toAsyncConc(1); 
            break;
         case ASYNCMUTEX:
            cout << "--> (1) Call from sync conc to async mutex (NOT RECOMMENDED)" << popcendl;
            (*__POPThis_POPObject).toAsyncMutex(1); 
            break;     
      }
   }
}

/** 
 * Calling any semantics from a synchronous sequential method
 * @param sem  Semantic to use for the internal call
 */
void POPObject::fromSyncSeq(int sem)
{
    if(__POPThis_POPObject != NULL){
      switch(sem){
         case SYNCSEQ:
            cout << "--> (2) Call from sync seq to sync seq (NOT POSSIBLE)" << popcendl;
            break;
         case SYNCCONC:
            cout << "--> (2) Call from sync seq to sync conc" << popcendl;
            (*__POPThis_POPObject).toSyncConc(2); 
            break;
         case SYNCMUTEX:           
            cout << "--> (2) Call from sync seq to sync mutex (NOT POSSIBLE)" << popcendl;
            break;
         case ASYNCSEQ:
            cout << "--> (2) Call from sync seq to async seq" << popcendl;
            (*__POPThis_POPObject).toAsyncSeq(2); 
            break;
         case ASYNCCONC:
            cout << "--> (2) Call from sync seq to async conc" << popcendl;
            (*__POPThis_POPObject).toAsyncConc(2); 
            break;
         case ASYNCMUTEX:
            cout << "--> (2) Call from sync seq to async mutex (NOT RECOMMENDED)" << popcendl;
            (*__POPThis_POPObject).toAsyncMutex(2); 
            break;     
      }
   }
}

/** 
 * Calling any semantics from a synchronous mutex method
 * @param sem  Semantic to use for the internal call
 */
void POPObject::fromSyncMutex(int sem)
{
      if(__POPThis_POPObject != NULL){
      switch(sem){
         case SYNCSEQ:
            cout << "--> (3) Call from sync mutex to sync seq (NOT POSSIBLE)" << popcendl; 
            break;
         case SYNCCONC:
            cout << "--> (3) Call from sync mutex to sync conc (NOT POSSIBLE)" << popcendl;
            break;
         case SYNCMUTEX:           
            cout << "--> (3) Call from sync mutex to sync mutex (NOT POSSIBLE)" << popcendl;
            break;
         case ASYNCSEQ:
            cout << "--> (3) Call from sync mutex to async seq" << popcendl;
            (*__POPThis_POPObject).toAsyncSeq(3); 
            break;
         case ASYNCCONC:
            cout << "--> (3) Call from sync mutex to async conc" << popcendl;
            (*__POPThis_POPObject).toAsyncConc(3); 
            break;
         case ASYNCMUTEX:
            cout << "--> (3) Call from sync mutex to async mutex (NOT RECOMMENDED)" << popcendl;
            (*__POPThis_POPObject).toAsyncMutex(3); 
            break;     
      }
   }
}

/** 
 * Calling any semantics from an asynchronous concurrent method
 * @param sem  Semantic to use for the internal call
 */
void POPObject::fromAsyncConc(int sem)
{
  if(__POPThis_POPObject != NULL){
      switch(sem){
         case SYNCSEQ:
            cout << "--> (4) Call from async conc to sync seq" << popcendl;
            (*__POPThis_POPObject).toSyncSeq(4); 
            break;
         case SYNCCONC:
            cout << "--> (4) Call from async conc to sync conc" << popcendl;
            (*__POPThis_POPObject).toSyncConc(4); 
            break;
         case SYNCMUTEX:           
            cout << "--> (4) Call from async conc to sync mutex (NOT POSSIBLE)" << popcendl;
            break;
         case ASYNCSEQ:
            cout << "--> (4) Call from async conc to async seq" << popcendl;
            (*__POPThis_POPObject).toAsyncSeq(4); 
            break;
         case ASYNCCONC:
            cout << "--> (4) Call from async conc to async conc" << popcendl;
            (*__POPThis_POPObject).toAsyncConc(4); 
            break;
         case ASYNCMUTEX:
            cout << "--> (4) Call from async conc to async mutex (NOT RECOMMENDED)" << popcendl;
            break;     
      }
   }
}

/** 
 * Calling any semantics from an asynchronous sequential method
 * @param sem  Semantic to use for the internal call
 */
void POPObject::fromAsyncSeq(int sem)
{
   if(__POPThis_POPObject != NULL){
      switch(sem){
         case SYNCSEQ:
            cout << "--> (5) Call from async seq to sync seq (NOT POSSIBLE)" << popcendl;
            break;
         case SYNCCONC:
            cout << "--> (5) Call from async seq to sync conc" << popcendl;
            (*__POPThis_POPObject).toSyncConc(5); 
            break;
         case SYNCMUTEX:           
            cout << "--> (5) Call from async seq to sync mutex (NOT POSSIBLE)" << popcendl;
            break;
         case ASYNCSEQ:
            cout << "--> (5) Call from async seq to async seq" << popcendl;
            (*__POPThis_POPObject).toAsyncSeq(5); 
            break;
         case ASYNCCONC:
            cout << "--> (5) Call from async seq to async conc" << popcendl;
            (*__POPThis_POPObject).toAsyncConc(5); 
            break;
         case ASYNCMUTEX:
            cout << "--> (5) Call from async seq to async mutex (NOT RECOMMENDED)" << popcendl;
            (*__POPThis_POPObject).toAsyncMutex(5); 
            break;     
      }
   }
}

/** 
 * Calling any semantics from an asynchronous mutex method
 * @param sem  Semantic to use for the internal call
 */
void POPObject::fromAsyncMutex(int sem)
{
  if(__POPThis_POPObject != NULL){
      switch(sem){
         case SYNCSEQ:
            cout << "--> (6) Call from async mutex to sync seq (NOT POSSIBLE)" << popcendl;
            break;
         case SYNCCONC:
            cout << "--> (6) Call from async mutex to sync conc (NOT POSSIBLE)" << popcendl;
            break;
         case SYNCMUTEX:           
            cout << "--> (6) Call from async mutex to sync mutex (NOT POSSIBLE)" << popcendl;
            break;
         case ASYNCSEQ:
            cout << "--> (6) Call from async mutex to async seq" << popcendl;
            (*__POPThis_POPObject).toAsyncSeq(6); 
            break;
         case ASYNCCONC:
            cout << "--> (6) Call from async mutex to async conc" << popcendl;
            (*__POPThis_POPObject).toAsyncConc(6); 
            break;
         case ASYNCMUTEX:
            cout << "--> (6) Call from async mutex to async mutex (NOT RECOMMENDED)" << popcendl;
            (*__POPThis_POPObject).toAsyncMutex(6); 
            break;     
      }
   }
}

/** 
 * Method called with the keyowrd this to check semantic behavior
 * @param callerid   ID of the calling method
 */
void POPObject::toSyncConc(int callerid)
{
   cout << "<-- (" << callerid << ") Call to sync conc SUCCEED" << popcendl;
}

/** 
 * Method called with the keyowrd this to check semantic behavior
 * @param callerid   ID of the calling method
 */
void POPObject::toSyncSeq(int callerid)
{
   cout << "<-- (" << callerid << ") Call to sync seq SUCCEED" << popcendl;
}

/** 
 * Method called with the keyowrd this to check semantic behavior
 * @param callerid   ID of the calling method
 */
void POPObject::toSyncMutex(int callerid)
{
   cout << "<-- (" << callerid << ") Call to sync mutex SUCCEED" << popcendl;
}

/** 
 * Method called with the keyowrd this to check semantic behavior
 * @param callerid   ID of the calling method
 */
void POPObject::toAsyncConc(int callerid)
{
   cout << "<-- (" << callerid << ") Call to async conc SUCCEED" << popcendl;
}

/** 
 * Method called with the keyowrd this to check semantic behavior
 * @param callerid   ID of the calling method
 */
void POPObject::toAsyncSeq(int callerid)
{
   cout << "<-- (" << callerid << ") Call to async seq SUCCEED" << popcendl;
}

/** 
 * Method called with the keyowrd this to check semantic behavior
 * @param callerid   ID of the calling method
 */
void POPObject::toAsyncMutex(int callerid)
{
   cout << "<-- (" << callerid << ") Call to async mutex SUCCEED" << popcendl;
}

@pack(POPObject);
