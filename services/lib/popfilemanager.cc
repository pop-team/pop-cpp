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
POPFileManager::POPFileManager(const std::string& challenge, bool deamon, std::string host)
    : pop_service_base(challenge) {
    popfile_log("[POPFILEMANAGER] POPFileManager created.");
    if (deamon) {
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
bool POPFileManager::createStrip(std::string absolutePath) {
    popfile_log("[POPFILEMANAGER] Creating strip: %s", absolutePath.c_str());
    std::ofstream strip;
    strip.open(absolutePath.c_str());

    if (strip.is_open()) {
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
void POPFileManager::writeToStrip(std::string stringName, std::string data) {
    std::ofstream strip;
    strip.open(stringName.c_str(), std::ios::out | std::ios::app);
    if (strip.is_open()) {
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
void POPFileManager::writeToRemoteStrip(std::string stringName, std::string data, pop_accesspoint ap) {
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
std::string POPFileManager::readFromStrip(std::string stripName, long start, long offset) {
    int length = 0;
    std::ifstream strip;
    strip.open(stripName.c_str(), std::ios::binary);

    strip.seekg(0, std::ios::end);  // Seek to end
    length = strip.tellg();         // Get length of the strip
    if (start >= length) {
        std::string p;
        return p;
    }

    strip.seekg(0, std::ios::beg);
    int crt_pos = strip.tellg();
    strip.seekg(start, std::ios::cur);
    char* buffer = new char[offset + 1];
    buffer[offset] = '\0';
    strip.read(buffer, offset);
    strip.close();
    std::string data(buffer);
    delete[] buffer;
    return data;
}

/**
 * POPFile: clementval
 * Save the accesspoint of POPSearchNode
 * @param Access Point of the POPCSearchNode
 * @return void
 */
void POPFileManager::setPSNAccessPoint(pop_accesspoint ap) {
    psn_ap = ap;
}

/**
 * POPFile: clementval
 * Get list of neighbors as a string and create AP
 * @return void
 */
void POPFileManager::getNeighborsFromPSN() {
    POPCSearchNode psn(psn_ap);
    std::string neighborsList = psn.getNeighborsAsString();
    std::string lstNeighbors = neighborsList.c_str();

    std::size_t found = lstNeighbors.find_first_of(";");

    while (found != std::string::npos) {
        std::string ap = lstNeighbors.substr(0, found);
        lstNeighbors = lstNeighbors.substr(found + 1);

        std::size_t port_separator = ap.find_last_of(":");

        if (port_separator != std::string::npos) {
            ap = ap.substr(0, port_separator + 1);
            ap.append("2712");
            pop_accesspoint neighborAP;
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
int POPFileManager::findResourcesForStrip(int nb, pop_accesspoint* candidates, std::string* stripNames,
                                          std::string stripPrefix, bool local) {
    int index = 0;
    int maxStrip = nb;

    // If a local strip is already present. Set the index to the next empty places.
    if (local) {
        index = 1;
        nb -= 1;
    }
    std::string str_stripname(stripPrefix.c_str());
    str_stripname.append("_strip");
    popfile_log("[POPFILEMANAGER] Look for %d nodes for strips", nb);

    for (std::list<pop_accesspoint>::iterator it = pfm_neighbors.begin(); it != pfm_neighbors.end(); it++) {
        popfile_log("[POPFILEMANAGER] Check creation of strip on %s", (*it).GetAccessString().c_str());
        POPFileManager tmpPfm((*it));
        std::string strip = str_stripname;
        std::stringstream intconverter;
        intconverter << index;
        strip.append(intconverter.str());
        std::string stripname(strip.c_str());

        if (tmpPfm.createStrip(stripname)) {
            candidates[index] = (*it);  // store accesspoint of the node on which the strip is created
            stripNames[index] = stripname;  // store the strip name
            popfile_log("[POPFILEMANAGER] Strip created on %s - %s", (*it).GetAccessString().c_str(),
                        stripname.c_str());
            index++;
            if (index == maxStrip) {
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
int popfile_log(const char* format, ...) {
    char* tmp = getenv("POPC_TEMP");
    std::string logfile = "/tmp/popfile.log";

    if (tmp) {
        logfile = std::string(tmp) + "/popfile_log";
    } 
    FILE* f = fopen(logfile.c_str(), "a");
    if (!f) {
        return 1;
    }

    time_t t = time(NULL);
    fprintf(f, "%s", ctime(&t));
    va_list ap;
    va_start(ap, format);
    vfprintf(f, format, ap);
    fprintf(f, "%s", "\n");
    va_end(ap);
    fclose(f);
    return 0;
}
