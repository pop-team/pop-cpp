/**
 * File : secure_jobmgr.ph
 * Author : Valentin Clément
 * Description : Declarataion of the parallel object SecureJobMgr
 * Creation date : 2010/12/07
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval  2010/12/07  Creation of this file
 */
#ifndef SECURE_JOBMGR_PH
#define SECURE_JOBMGR_PH

#include "jobmgr.ph"

parclass SecureJobMgr: public JobMgr {
public:
   classuid(1100);
   //VirtSecureJobMgr constructor
   SecureJobMgr(bool daemon, [in] const POPString &conf, 
      [in] const POPString &challenge, const POPString &url, 
      const paroc_accesspoint &nodeAccess, const paroc_accesspoint &psmRef) @{ od.url(url); od.runLocal(true); od.service(true); };
   
   //VirtSecureJobMgr destructor
   ~SecureJobMgr();

   
   //Overwritten method (JobMgr)
   sync conc virtual bool  AllocResource(const paroc_accesspoint &localservice, const POPString &objname, const paroc_od &od, 
      int howmany, [in,out, size=howmany] float *fitness, [in,out, size=howmany] paroc_accesspoint *jobcontacts, 
      [in,out, size=howmany] int *reserveIDs, [in] int requestInfo[3], [in] int trace[MAX_HOPS], [in] int tracesize);


private:
   POPString _localPublicKey;    //Copy of the local public key used by the ressource discovery

   
};

int paroc_service_log(const char *format,...);
int popc_node_log(const char *format,...);

#endif
