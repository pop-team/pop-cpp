/**
 * File : ESXWrapper.h
 * Author : Adrian Wyssen
 * Description : Implementation of the VPopCWrapper for an ESX driver
 * Creation date : 04/08/2010
 * 
 * Modifications :
 * Authors		Date			Comment
 * clementval  2010/1/27   move all non-secific methods to the POPWrapper header
 */

#ifndef ESXWRAPPER_H
#define ESXWRAPPER_H


#include "POPWrapper.h"
#include "popvm.h"
#include "paroc_accesspoint.h"

extern "C"{
   #include <libvirt/libvirt.h>
   #include <libvirt/virterror.h>
}
#include <cstring>


class ESXWrapper : public POPWrapper {
   //Private attributes
private:
   string _ESX_hostname;      // The hostname of the hypervisor
   string _ESX_ipaddress;     // IP address of the hypervisor
   string _ESX_sdkurl;        // SDK address of the hypervisor
   string _ESX_domName;       // The domain name to which the instance is connected
   string _ESX_user;          // The user to connect to a hypervisor
   string _ESX_pass;          // The password for the hypervisor
   
   
   
public:
   ESXWrapper(paroc_accesspoint clonerRef);
   ~ESXWrapper(); 
   
   /* Please check out VPopCWrapper for any comments */
   int _popc_connectOpenAuth(string uri, string user, string password);
   int _popc_domainGetIpAddress(POPvm &vm);
   int _popc_sendLocalPublicKey(POPvm &vm);
   int _popc_sendPublicKey(POPvm &vm, POPString pki);
   int _popc_getLocalPublicKey(POPvm &vm);
   int _popc_domainClone(POPvm &original, int number, POPString baseName, int suffix, paroc_accesspoint clonerAP);
   int _popc_domainWaitingForTools(POPvm &vm);
   

private:
   void _ESXWrapper_executeClone(POPvm &original, POPvm &clone);
};

int popc_wrapper_log(const char *format,...);

#endif /* ESXWRAPPER_H */
