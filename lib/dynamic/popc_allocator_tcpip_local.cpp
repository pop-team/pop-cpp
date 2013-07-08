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

#define ALLOC_TIMEOUT 60
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
    POPString p;
    POPString hostname;
    POPString cwd;
    
    char tmpstr[10240];
    char *argv[1024];
    
	od.getProtocol(p);
        od.getURL(hostname);
        od.getDirectory(cwd);
	
        int n = 0;
	
	// Get the executable path name
	POPString codefile;
	od.getExecutable(codefile);

	// If od.executable is not defined, throw an exception as the parallel object couldn't be allocated
	if(codefile.Length() <= 0) {
	  printf("POP-C++ Error: Code file executable path is NULL ! Abort !\n"); 	
	  paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname);	  
	}

        if(hostname == NULL) hostname = paroc_system::GetHost();
        
        /**
	 * Create a combox to allocate the new parallel object.
	 */
        paroc_combox_factory* combox_factory = paroc_combox_factory::GetInstance();
	if (combox_factory == NULL) 
	  paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname);
	
	paroc_combox* tmpsock = combox_factory->Create("socket");
        
        if(tmpsock == NULL)
                paroc_exception::paroc_throw(POPC_NO_PROTOCOL, objectname);
                
        bool isServer=true;
	
        if (!tmpsock->Create(0, isServer)) paroc_exception::paroc_throw_errno();
        
        paroc_connection *connection = tmpsock->get_connection();        
        
        POPString cburl;
	tmpsock->GetUrl(cburl);
        
        argv[n++]=strdup(codefile);

        sprintf(tmpstr,"-object=%s", objectname.GetString());
        argv[n++]=strdup(tmpstr);
        
	sprintf(tmpstr,"-callback=%s", (const char*)cburl);
	argv[n++]=strdup(tmpstr);

	
	// Select core
	/*if (rcore!=NULL&&rcore!=0) {
		sprintf(tmpstr,"-core=%s",(const char*)rcore);
		argv[n++]=strdup(tmpstr);
	}*/

	
#ifdef OD_DISCONNECT
	if (checkConnection) {
		sprintf(tmpstr,"-checkConnection");
		argv[n++]=strdup(tmpstr);
	}
#endif	

	// Add the working directory as argument
	if (cwd!=NULL && *cwd!=0) {
		sprintf(tmpstr,"-cwd=%s",(const char*)cwd);
		argv[n++]=strdup(tmpstr);
	}

	argv[n]=NULL;

	int ret=0, err=0;
	
        ret = RunCmd(argv, NULL);
        err = errno;
        
	for (int i=0;i<n;i++) if (argv[i]!=NULL) free(argv[i]);

	if (ret==-1)
	{
		DEBUG("Can not start the object code...");
		paroc_exception::paroc_throw(err, "POPObject");
	}

	//Now get the return paroc_accesspoint....
	tmpsock->SetTimeout(ALLOC_TIMEOUT*1000);
        
        paroc_buffer_xdr buf1;
        paroc_buffer *tmpbuffer=&buf1;        
       
        //printf("[Interface Side] [[allocate]]\n");//vanhieu.nguyen            
        if (!tmpbuffer->Recv((*tmpsock), connection))
            paroc_exception::paroc_throw_errno();
                
        paroc_buffer::CheckAndThrow(*tmpbuffer);
        
        tmpbuffer->Push("status","int",1);
        tmpbuffer->UnPack(&n,1);
        tmpbuffer->Pop();
        
        POPString objectaddress;
        tmpbuffer->Push("objectaddress","paroc_accesspoint",1);
        tmpbuffer->UnPack(&objectaddress, 1);
        tmpbuffer->Pop();
        
        tmpsock->Close();
        
        return objectaddress;  
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
