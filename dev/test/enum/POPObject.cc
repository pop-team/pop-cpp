#include "POPObject.ph"
#include <unistd.h>

POPObject::POPObject()
{
   enum Days{Sunday,Monday,Tuesday,Wednesday,Thursday,Friday,Saturday};
   cout << "POPCobject created (by JobMgr) on machine:" << GetAccessPoint().GetAccessString() << popcendl;
}

POPObject::~POPObject()
{
   cout << "POPCobject: on machine:" << (const char*)POPSystem::GetHost() <<" is being destroyed" << popcendl;
}

/** 
 * Calling any semantics from a synchronous sequential method
 * @param sem  Semantic to use for the internal call
 */
void POPObject::fromSyncSeq(int sem)
{


}

@pack(POPObject);
