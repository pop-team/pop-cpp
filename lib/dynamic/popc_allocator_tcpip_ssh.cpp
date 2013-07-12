/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Valentin Clement
 * @date 2012/12/04
 * @brief Declaration of the base class POPC_AllocatorFactory. The allocator factory allows to provide the right allocator for 
 *        parallel object allocation depending the lower layer (SSH, MPI, POP-C++ MPI Interconnector ...). 
 *
 *
 */

#include "popc_allocator_tcpip.h"

#include "paroc_system.h"
#include "paroc_exception.h"
#include "paroc_combox.h"
#include "paroc_combox_factory.h"
#include "paroc_broker.h"
#include "include/pseudodynamic/paroc_system.h"
#include "include/pseudodynamic/paroc_interface.h"

#define ALLOC_TIMEOUT 60
/**
 * Allocator over TCP/IP with local mechanism constructor
 */ 
POPC_Allocator_tcpip_ssh::POPC_Allocator_tcpip_ssh()
{
}

/**
 * Allocator over TCP/IP with local mechanism destrcutor
 */ 
POPC_Allocator_tcpip_ssh::~POPC_Allocator_tcpip_ssh()
{
}

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @return A string representation of the access-point
 */
POPString POPC_Allocator_tcpip_ssh::allocate(POPString& objectname, paroc_od& od)
{
    //paroc_accesspoint jobcontact, remotejobcontact;
    POPString objectaddress;   
    
    //Exec using JobMgr interface...
    /*POPString platforms;
    od.getPlatforms(platforms);

    if (platforms.Length()<=0)
    {
            CodeMgr mgr(paroc_system::appservice);
            if (mgr.GetPlatform(objectname, platforms)<=0)
            {
                    paroc_exception::paroc_throw(OBJECT_EXECUTABLE_NOTFOUND, objectname);
            }
            od.setPlatforms(platforms);
    }
    //Global Resource management system --> Find a resource.

    POPString joburl;
    od.getJobURL(joburl);


    if  (joburl!=NULL)
    {
            jobcontact.SetAccessString(joburl);
    } else jobcontact=paroc_system::jobservice;

    if (jobcontact.IsEmpty())
    {
            char str[1024];
            DEBUG("INTERFACE - JOBMGR %s", (const char *)paroc_system::GetHost());
            sprintf(str,"%s:%d",(const char *)paroc_system::GetHost(),DEFAULTPORT);
            jobcontact.SetAccessString(str);
    }

    try
    {
            DEBUG("JOBMGR --> connect to %s\n", jobcontact.GetAccessString());
            JobCoreService resources(jobcontact);
            int ret;
            if (batchindex==0 && batchsize>1)
            {
                    if (batchaccesspoint!=NULL) delete [] batchaccesspoint;
                    batchaccesspoint=new paroc_accesspoint[batchsize];
                    DEBUG("Create Object : %s\n", ClassName());
//TODO put an other array than batchaccesspoint
                    ret=resources.CreateObject(paroc_system::appservice,objectname,od, batchsize,  batchaccesspoint, batchsize, batchaccesspoint);
                    if (ret==0) objectaddress=batchaccesspoint[batchindex++];
                    DEBUG("Return %d", ret);
            }
            else{

                    DEBUG("Create Object : %s\n", ClassName());
                    ret=resources.CreateObject(paroc_system::appservice,objectname,od, 1,  &objectaddress, 1, &remotejobcontact);
                    DEBUG("Return %d", ret);
            }

            if (ret!=0) paroc_exception::paroc_throw(ret,ClassName());



            //Get the POPAppID
            AppCoreService acs(paroc_system::appservice);
            popAppId = acs.GetPOPCAppID();         

    }
    catch (paroc_exception * e)
    {
            paroc_system::perror(e);
            paroc_exception::paroc_throw(POPC_JOBSERVICE_FAIL,"POP-C++ error: Cannot create object via POP-C++ Job Manager");
    }*/
                
    return objectaddress;
}

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @param nb          The number of object to allocate in the group
 * @return A pointer to a single combox connected with the group
 */
paroc_combox* POPC_Allocator_tcpip_ssh::allocate_group(POPString& objectname, paroc_od& od, int nb)
{

  /* Allocation process here */  
  
  return NULL; 
}
