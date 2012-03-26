/**
 * File : virtual_secure_jobmgr.ph
 * Author : Valentin Clément
 * Description : Declarataion of the parallel object VirtSecureJobMgr
 * Creation date : 2010/12/07
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval  2010/12/07  Creation of this file
 */
#ifndef VIRTUAL_SECURE_JOBMGR_PH
#define VIRTUAL_SECURE_JOBMGR_PH

#include "virtual_jobmgr.ph"

parclass VirtSecureJobMgr: public VirtualJobMgr {
public:
   classuid(1100);
   //VirtSecureJobMgr constructor
   VirtSecureJobMgr(bool daemon, [in] const POPString &virtconf, [in] const POPString &conf, 
      [in] const POPString &challenge, const POPString &url, 
      const paroc_accesspoint &nodeAccess, const paroc_accesspoint &clonerRef, const paroc_accesspoint &psmRef) @{ od.url(url); od.runLocal(true); od.service(true);};
   
   //VirtSecureJobMgr destructor
   ~VirtSecureJobMgr();

   
   //Overwritten method (JobMgr)
   sync conc virtual bool  AllocResource(const paroc_accesspoint &localservice, const POPString &objname, const paroc_od &od, 
      int howmany, [in,out, size=howmany] float *fitness, [in,out, size=howmany] paroc_accesspoint *jobcontacts, 
      [in,out, size=howmany] int *reserveIDs, [in] int requestInfo[3], [in] int trace[MAX_HOPS], [in] int tracesize);

   sync seq void writePKIToVM(POPString popAppId, POPString pki);
   sync seq POPString getVMPKI(POPString popAppId);

protected:
   //Prepare the VM for the execution
   virtual bool PrepareVM(char** argv, int* n, POPString popAppId, POPString reqID);
   

private:
   POPString _localPublicKey;    //Copy of the local public key used by the ressource discovery
   
};

int paroc_service_log(const char *format,...);
int popc_node_log(const char *format,...);

#endif
