/**
 * File: popfilemanager.cc
 * Author: Valentin Clement (clementval)
 * Description: Implementation of the parallel object POPFileManager. This object is in charge of POPFile management.
 * Creation date: 03.25.2012
 *
 * Change Log:
 * Author       Date            Description
 * clementval   03.25.2012  Creation of this file
 */

#include "popfilemanager.ph"
#include "popc_search_node.ph"

#include "popc_intface.h"

#include <sstream>
#include <fstream>

/**
 * Constructor of the POPFileManager with object description
 * @param challenge A challenge string to stop the service
 * @param deamon        Boolean flag to set the service as a deamon or not
 * @param host          The url to create the service
 */
POPFileManager::POPFileManager(const POPString &challenge, bool deamon, POPString host) : paroc_service_base(challenge) {
    popfile_log("[POPFILEMANAGER] POPFileManager created.");
    if(deamon) {
        Start();
    }
}

/**
 * Destructor of the POPFileManager
 */
POPFileManager::~POPFileManager() {

}

/**
 * Create a strip file on the local computer
 * @param absolutePath  The absolute path and filename of the strip file to create
 * @return TRUE if the file was created successfully. FALSE in all others cases.
 */
bool POPFileManager::createStrip(POPString absolutePath) {
    popfile_log("[POPFILEMANAGER] Creating strip: %s", absolutePath.c_str());
    std::ofstream strip;
    strip.open(absolutePath.c_str());

    if(strip.is_open()) {
        strip.close();
        popfile_log("[POPFILEMANAGER] Strip created on local storage: %s", absolutePath.c_str());
        return true;
    }

    return false;
}

/**
 * POPFile: clementval
 * Write data to a local strip
 * @param stringName    absloute path to the strip
 * @param data          Actual data to write to the strip
 * @return void
 */
void POPFileManager::writeToStrip(POPString stringName, POPString data) {
    std::ofstream strip;
    strip.open(stringName.c_str(), std::ios::out | std::ios::app);
    if(strip.is_open()) {
        strip << data.c_str();
        strip.close();
    } else {
        popfile_log("[POPFILEMANAGER] Attempt to write data to %s failed", stringName.c_str());
    }
}

/**
 * POPFile: clementval
 * Call a remote PFM to write to a remote strip
 * @param stringName    absloute path to the strip
 * @param data          Actual data to write to the strip
 * @param ap            Access point of thre remote PFM
 * @return void
 */
void POPFileManager::writeToRemoteStrip(POPString stringName, POPString data, paroc_accesspoint ap) {
    POPFileManager remote(ap);
    remote.writeToStrip(stringName, data);
}

/**
 * POPFile: clementval
 * Read from a local strip
 * @param stringName    absloute path to the strip
 * @param begin     Size to begin to read
 * @param offset        Site to read
 * @return Data retrieved from the strip
 */
POPString POPFileManager::readFromStrip(POPString stripName, long start, long offset) {
    int length=0;
    std::ifstream strip;
    strip.open(stripName.c_str(), ios::binary);

    strip.seekg(0, ios::end);       // Seek to end
    length = strip.tellg();         // Get length of the strip
    if(start >= length) {
        POPString p;
        return p;
    }

    strip.seekg(0, ios::beg);
    int crt_pos = strip.tellg();
    strip.seekg(start, ios::cur);
    char* buffer;
    buffer = new char[offset+1];
    buffer[offset] = '\0';
    strip.read(buffer, offset);
    strip.close();
    POPString data(buffer);
    delete [] buffer; // TODO Check it
    return data;
}

/**
 * POPFile: clementval
 * Save the accesspoint of POPSearchNode
 * @param Access Point of the POPCSearchNode
 * @return void
 */
void POPFileManager::setPSNAccessPoint(paroc_accesspoint ap) {
    psn_ap = ap;
}

/**
 * POPFile: clementval
 * Get list of neighbors as a string and create AP
 * @return void
 */
void POPFileManager::getNeighborsFromPSN() {
    POPCSearchNode psn(psn_ap);
    POPString neighborsList = psn.getNeighborsAsString();
    std::string lstNeighbors = neighborsList.c_str();

    std::size_t found=lstNeighbors.find_first_of(";");

    while(found!=std::string::npos) {
        std::string ap = lstNeighbors.substr(0, found);
        lstNeighbors = lstNeighbors.substr(found+1);

        std::size_t port_separator = ap.find_last_of(":");

        if(port_separator != std::string::npos) {
            ap = ap.substr(0, port_separator+1);
            ap.append("2712");
            paroc_accesspoint neighborAP;
            popfile_log("[POPFILEMANAGER] Neighbors is %s", ap.c_str());
            neighborAP.SetAccessString(ap.c_str());
            pfm_neighbors.push_back(neighborAP);
        } else {
            popfile_log("[POPFILEMANAGER] Could not find port separator");
        }

        found = lstNeighbors.find_first_of(";");
    }
}

/**
 * TODO use the PSN to perform an intelligent Resource Discovery
 * Find storage resources to store the strips of a new parallel file
 * @param nb                The number of desired strips
 * @param candidates        An output array that will store the candidates for the strips
 * @param strNames      An output array that will store the real strip names
 * @param stripPrefix   The prefix used to create strip names
 * @param local         If TRUE, there is a local strip
 * @return The actual number of strip created
 */
int POPFileManager::findResourcesForStrip(int nb, paroc_accesspoint* candidates, POPString* stripNames, POPString stripPrefix, bool local) {
    int index=0;
    int maxStrip = nb;

    // If a local strip is already present. Set the index to the next empty places.
    if(local) {
        index=1;
        nb -= 1;
    }
    std::string str_stripname(stripPrefix.c_str());
    str_stripname.append("_strip");
    popfile_log("[POPFILEMANAGER] Look for %d nodes for strips", nb);

    for(std::list<paroc_accesspoint>::iterator it = pfm_neighbors.begin(); it != pfm_neighbors.end(); it++) {
        popfile_log("[POPFILEMANAGER] Check creation of strip on %s", (*it).GetAccessString().c_str());
        POPFileManager tmpPfm((*it));
        std::string strip = str_stripname;
        std::stringstream intconverter;
        intconverter << index;
        strip.append(intconverter.str());
        POPString stripname(strip.c_str());

        if(tmpPfm.createStrip(stripname)) {
            candidates[index] = (*it);      //store accesspoint of the node on which the strip is created
            stripNames[index] = stripname;  //store the strip name
            popfile_log("[POPFILEMANAGER] Strip created on %s - %s", (*it).GetAccessString().c_str(), stripname.c_str());
            index++;
            if(index == maxStrip) {
                break;
            }
        }
    }

    return index;
}

/**
 * Method used to write log
 * @param String with format
 * @return Error information
 */
int popfile_log(const char *format,...) {
    char *tmp=getenv("POPC_TEMP");
    char logfile[256];

    if(tmp) {
        sprintf(logfile,"%s/popfile_log",tmp);
    } else {
        strcpy(logfile, "/tmp/popfile.log");
    }

    FILE *f=fopen(logfile,"a");
    if(!f) {
        return 1;
    }

    time_t t=time(NULL);
    fprintf(f,"%s", ctime(&t));
    va_list ap;
    va_start(ap, format);
    vfprintf(f, format, ap);
    fprintf(f,"%s","\n");
    va_end(ap);
    fclose(f);
    return 0;
}
