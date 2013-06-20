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
#include "paroc_interface.h"


int paroc_interface::batchindex=0;
int paroc_interface::batchsize=0;
paroc_accesspoint * paroc_interface::batchaccesspoint=NULL;

/**
 * Allocator over TCP/IP with local mechanism constructor
 */ 
POPC_Allocator_tcpip_local::POPC_Allocator_tcpip_local()
{
}

/**
 * Allocator over TCP/IP with local mechanism destrcutor
 */ 
POPC_Allocator_tcpip_local::~POPC_Allocator_tcpip_local()
{
}

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @return A string representation of the access-point
 */
POPString POPC_Allocator_tcpip_local::allocate(POPString& objectname, paroc_od& od)
{
    paroc_interface *paroc_intf = new paroc_interface();
    
    printf("--------------------Allocate--------------------\n");
	POPString p;
	od.getProtocol(p);
               
	paroc_accesspoint jobcontact, objaccess, remotejobcontact;

	// With the actual code, batchsize is always zero
        
        printf("p=%s\n", p.GetString());
        printf("paroc_interface::batchindex=%d\n", paroc_interface::batchindex);
        printf("paroc_interface::batchsize=%d\n", paroc_interface::batchsize);
	if (!paroc_intf->TryLocal(objaccess, od))
	{
                POPString objname(paroc_intf->ClassName());

		//Exec using JobMgr interface...
		POPString platforms;
		od.getPlatforms(platforms);

		if (platforms.Length()<=0)
		{                    
                    paroc_exception::paroc_throw(OBJECT_EXECUTABLE_NOTFOUND, paroc_intf->ClassName());
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
                printf("INTERFACE - JOBMGR %s", (const char *)paroc_system::GetHost());
			sprintf(str,"%s:%d",(const char *)paroc_system::GetHost(),DEFAULTPORT);
			jobcontact.SetAccessString(str);
		}

		try
		{
			printf("JOBMGR --> connect to %s\n", jobcontact.GetAccessString());
			//JobCoreService resources(jobcontact);
			int ret;
			if (paroc_interface::batchindex==0 && paroc_interface::batchsize>1)
			{
				if (paroc_interface::batchaccesspoint!=NULL) delete [] paroc_interface::batchaccesspoint;
				paroc_interface::batchaccesspoint=new paroc_accesspoint[paroc_interface::batchsize];
				printf("Create Object : %s\n", paroc_intf->ClassName());
                                //TODO put an other array than batchaccesspoint
				//ret=resources.CreateObject(paroc_system::appservice,objname,od, batchsize,  batchaccesspoint, batchsize, batchaccesspoint);
				if (ret==0) objaccess=paroc_interface::batchaccesspoint[paroc_interface::batchindex++];
                                printf("Return %d", ret);
			}
			else{
            
				printf("Create Object : %s\n", paroc_intf->ClassName());
                                //ret=resources.CreateObject(paroc_system::appservice,objname,od, 1,  &objaccess, 1, &remotejobcontact);
                                printf("Return %d", ret);
			}

			if (ret!=0) paroc_exception::paroc_throw(ret,paroc_intf->ClassName());
         


                        //Get the POPAppID
                        //AppCoreService acs(paroc_system::appservice);
                        //popAppId = acs.GetPOPCAppID();      

		}
		catch (paroc_exception * e)
		{
			paroc_system::perror(e);
			paroc_exception::paroc_throw(POPC_JOBSERVICE_FAIL,"POP-C++ error: Cannot create object via POP-C++ Job Manager");
		}
	}
        //Add for SSH Tunneling
        if(od.isSecureSet()) objaccess.SetSecure();
        if(od.isServiceSet()) objaccess.SetAsService();
        
        printf("--------------------/endlAllocate-----------------\n");
        return objaccess.GetAccessString();
}

/**
 * Allocate a single object by using the TCP/IP protocol with a local allocation mechanism
 * @param objectname  Name of the object to be allocated
 * @param od          Object description used for allocation
 * @param nb          The number of object to allocate in the group
 * @return A pointer to a single combox connected with the group
 */
paroc_combox* POPC_Allocator_tcpip_local::allocate_group(POPString& objectname, paroc_od& od, int nb)
{

  /* Allocation process here */  
  
  return NULL; 
}
