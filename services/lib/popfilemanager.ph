/**
 * File : popfilemanager.ph
 * Author : Valentin Clement (clementval)
 * Description : Declaration of the parallel object POPFileManager. This object is in charge of POPFile management.
 * Creation date : 03.25.2012
 *
 * Change Log:
 * Author       Date            Description
 * clementval   03.25.2012  Creation of this file
 */

#ifndef POPFILEMANAGER_H_INCLUDE
#define POPFILEMANAGER_H_INCLUDE

#include "paroc_service_base.ph"
#include "pop_accesspoint.h"
#include <list>

parclass POPFileManager :
virtual public paroc_service_base {
public:
    classuid(50);

    //POPFileManager constructor
    POPFileManager(const std::string &challenge, bool deamon, std::string host) @{ od.runLocal(true); od.service(true); od.url(host); };

    //POPFileManager destrcutor
    ~POPFileManager();

    //Create a new strip on this node
    sync seq bool createStrip(std::string abslotuePath);

    //Find resource to create strips
    sync conc int findResourcesForStrip(int nb, [in, out, size=nb] pop_accesspoint* candidate, [in, out, size=nb] std::string* stripNames, std::string stripPrefix, bool local);

    //Write to strip
    async conc void writeToStrip(std::string stripName, std::string data);

    //Write to a remote strip
    async conc void writeToRemoteStrip(std::string stringName, std::string data, pop_accesspoint ap);

    // Read a block of data from the strip
    sync conc std::string readFromStrip(std::string stripName, long start, long offset);

    //Save the accesspoint of the POPSearchNode
    sync seq void setPSNAccessPoint(pop_accesspoint ap);

    //Get neighbors to create strips on them
    sync seq void getNeighborsFromPSN();

private:
    pop_accesspoint psn_ap;   // Saved access point to the local PSN for resource discovery
    std::list<pop_accesspoint> pfm_neighbors; // list of direct neigbors

};

int popfile_log(const char *format,...);  //log function for error

#endif /* POPFILEMANAGER_H_INCLUDE_ */
