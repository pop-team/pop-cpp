/*
UPDATES :
Authors     Date            Comment
clementval  2010/04/19  All code added for the semester project begin with this comment     //Added by clementval
clementval  2010/04/19  All code modified during the semester project begins with //Modified by
clementval, ends with //End of modification
clementval  2010/05/10  Creating a POPCSearchNode before creating the JobMgr, change the JobMgr creation by passing the
POPCSearchNode access point
clementval  2012/04/12  Add POPFileManager service support
*/

#include "popc_intface.h"

#include "../../config.h"

#include "popfilemanager.ph"

/**
 * ViSaG : clementval
 * include the right files for the specified version
 */

#if defined POPC_SECURE_VIRTUAL
#include "virtual_secure_jobmgr.ph"
#include "popcloner.ph"
#elif defined POPC_VIRTUAL
#include "virtual_jobmgr.ph"
#include "popcloner.ph"
#elif defined POPC_SECURE
#include "secure_jobmgr.ph"
#else
#include "jobmgr.ph"
#endif

// Include VPSN, SPSN or PSN
#ifdef POPC_SECURE_VIRTUAL
#include "virtual_secure_popc_search_node.ph"
#elif defined POPC_VIRTUAL
#include "virtual_popc_search_node.ph"
#elif defined POPC_SECURE
#include "secure_popc_search_node.ph"
#else
#include "popc_search_node.ph"
#endif

// Include PSM or VPSM
#ifdef POPC_SECURE_VIRTUAL
#include "virtual_popc_security_manager.ph"
#elif defined POPC_VIRTUAL
#include "virtual_popc_security_manager.ph"
#elif defined POPC_SECURE
#include "popc_security_manager.ph"
#endif

/* ViSaG */

void Usage() {
    printf(
        "Usage: jobmgr_launcher [-servicepoint=<host>[:port]] [-port=<port>] <start [options]> | "
        "<stop>\n\tOptions:\n\t  [-code=<jobmgr code file>] [-conf=<jobmgr config file>] [-challenge=<string>] "
        "[-genchallenge=<out file>] [-proxy=<proxy contact>] [-test]\n");
    exit(1);
}

int main(int argc, char** argv) {
    std::string hostpfm;
    std::string conf;
    std::string virtconf;
    std::string objcode;
    std::string challenge;
    std::string str;
    /** TO BE REMOVED FOR 2.5 BUT KEEP FOR 3.0
    bool popfile_service = true; */

    char* tmp;
    bool stop = (pop_utils::checkremove(&argc, &argv, "stop") != NULL);
    if (!stop && pop_utils::checkremove(&argc, &argv, "start") == NULL) {
        Usage();
    }

    if ((tmp = pop_utils::checkremove(&argc, &argv, "-servicepoint=")) == NULL) {
        tmp = pop_utils::checkremove(&argc, &argv, "-port=");
        if (tmp == NULL) {
            str = pop_system::GetHost() + ":2711";
        } else {
            str = pop_system::GetHost() + ":" + tmp;
        }
    } else {
        str = tmp;
        if (str.find(':') == std::string::npos) {
            str += ":2711";
        }
    }

    /** TO BE REMOVED FOR 2.5 BUT KEEP FOR 3.0
        if(pop_utils::checkremove(&argc, &argv, "--no-service")){
        if(pop_utils::checkremove(&argc, &argv, "popfile"))
            popfile_service = false;
    }*/
    std::string host = str;
    str = pop_system::GetHost() + ":2712";
    hostpfm = str;

    tmp = pop_utils::checkremove(&argc, &argv, "-challenge=");
    if (tmp != NULL) {
        challenge = tmp;
    } else if ((tmp = pop_utils::checkremove(&argc, &argv, "-genchallenge=")) != NULL && !stop) {
        unsigned int seed = time(NULL);
        char tmpstr[256];
        for (int i = 0; i < 255; i++) {
            tmpstr[i] = static_cast<char>('A' + 23.0 * rand_r(&seed) / (RAND_MAX + 1.0));
        }
        tmpstr[255] = 0;
        challenge = tmpstr;
        int fd = creat(tmp, O_CREAT | S_IRUSR | S_IWUSR);
        if (fd < 0) {
            perror("Challenge output file");
            return 1;
        }
        if (popc_write(fd, tmpstr, 255) != 255) {
            perror("Error on writing challenge string");
            return 1;
        }
        popc_close(fd);
    }
    try {
        if (stop) {
#ifdef POPC_SECURE_VIRTUAL
            LOG_INFO("Stopping POP-C++ %s [Virtual Secure] Global Services", VERSION);
#elif defined POPC_SECURE
            LOG_INFO("Stopping POP-C++ %s [Secure] Global Services", VERSION);
#elif defined POPC_VIRTUAL
            LOG_INFO("Stopping POP-C++ %s [Virtual] Global Services", VERSION);
#else
            LOG_INFO("Stopping POP-C++ %s [Standard] Global Services", VERSION);
#endif

            pop_accesspoint jobmgr_ap;
            jobmgr_ap.SetAccessString(host.c_str());

#ifdef POPC_SECURE_VIRTUAL
            VirtSecureJobMgr mgr(jobmgr_ap);
            VirtSecurePOPCSearchNode vspsn(mgr.GetNodeAccessPoint());
            if (!vspsn.Stop(challenge)) {
                LOG_ERROR("[POP-C++ Runtime] Bad challenge string. Cannot stop VSPSN ...");
            } else {
                LOG_INFO("[POP-C++ Runtime] VSPSN stopped successfully!");
            }

            VirtualPOPCSecurityManager vpsm(mgr.getPSMRef());
            if (!vpsm.Stop(challenge)) {
                LOG_WARNING("[POP-C++ Runtime] Bad challenge string. Cannot stop VPSM ...");
            } else {
                LOG_INFO("[POP-C++ Runtime] VPSM stopped successfully!");
            }

            POPCloner pc(mgr.getPOPClonerRef());
            if (!pc.Stop(challenge)) {
                LOG_WARNING("[POP-C++ Runtime] Bad challenge string. Cannot stop POPCloner ...");
            } else {
                LOG_INFO("[POP-C++ Runtime] POPCloner stopped successfully!");
            }

#elif defined POPC_VIRTUAL
            VirtualJobMgr mgr(jobmgr_ap);
            VirtualPOPCSearchNode vpsn(mgr.GetNodeAccessPoint());
            if (!vpsn.Stop(challenge)) {
                LOG_WARNING("[POP-C++ Runtime] Bad challenge string. Cannot stop VPSN ...");
            } else {
                LOG_INFO("[POP-C++ Runtime] VPSN stopped successfully!");
            }

            POPCloner pc(mgr.getPOPClonerRef());
            if (!pc.Stop(challenge)) {
                LOG_WARNING("[POP-C++ Runtime] Bad challenge string. Cannot stop POPCloner ...");
            } else {
                LOG_INFO("[POP-C++ Runtime] POPCloner stopped successfully!");
            }

#elif defined POPC_SECURE
            SecureJobMgr mgr(jobmgr_ap);
            SecurePOPCSearchNode spsn(mgr.GetNodeAccessPoint());
            if (!spsn.Stop(challenge)) {
                LOG_WARNING("[POP-C++ Runtime] Bad challenge string. Cannot stop SPSN ...");
            } else {
                LOG_INFO("[POP-C++ Runtime] SPSN stopped successfully!");
            }

            POPCSecurityManager psm(mgr.getPSMRef());
            if (!psm.Stop(challenge)) {
                LOG_WARNING("[POP-C++ Runtime] Bad challenge string. Cannot stop PSM ...");
            } else {
                LOG_INFO("[POP-C++ Runtime] PSM stopped successfully!");
            }
#else
            JobMgr mgr(jobmgr_ap);
            try {
                pop_accesspoint pfm_ap;
                pfm_ap.SetAccessString("socket://127.0.0.1:2712");
                POPFileManager pfm(pfm_ap);
                if (!pfm.Stop(challenge)) {
                    LOG_ERROR("[POP-C++ Runtime] Bad challenge string. Cannot stop PFM ...");
                } else {
                    LOG_INFO("[POP-C++ Runtime] PFM stopped successfully!");
                }
            } catch (std::exception& e) {
                LOG_WARNING("Exception while creating POPFileManager: %s", e.what());
            }

            POPCSearchNode psn(mgr.GetNodeAccessPoint());
            if (!psn.Stop(challenge)) {
                LOG_WARNING("[POP-C++ Runtime] Bad challenge string. Cannot stop PSN ...");
            } else {
                LOG_INFO("[POP-C++ Runtime] PSN stopped successfully!");
            }
#endif

            if (!mgr.Stop(challenge)) {
                LOG_WARNING("[POP-C++ Runtime] Bad challenge string. Cannot stop JM ...");
                return 1;
            }

            LOG_INFO("[POP-C++ Runtime] JobMgr stopped successfully!");
            return 0;
        }

        if ((tmp = pop_utils::checkremove(&argc, &argv, "-conf=")) == NULL && (tmp = getenv("JOBMGR_CONF")) == NULL) {
            const char* tmp2 = getenv("POPC_LOCATION");
            if (tmp2 == NULL) {
                LOG_ERROR("POPC_LOCATION environment variable is not set.");
                Usage();
            }
            std::string paroc_location(tmp2);

            str = paroc_location + "/etc/jobmgr.conf";
            conf = str;

            str = paroc_location + "/etc/virtual.conf";
            virtconf = str;

        } else {
            conf = tmp;
        }

        bool daemon = (pop_utils::checkremove(&argc, &argv, "-test") == NULL);

/**
 * Instantiation of the right services
 */
#ifdef POPC_SECURE_VIRTUAL
        LOG_INFO("Starting POP-C++ %s [Virtual Secure] Global Services", VERSION);
#elif defined POPC_SECURE
        LOG_INFO("Starting POP-C++ %s [Secure] Global Services", VERSION);
#elif defined POPC_VIRTUAL
        LOG_INFO("Starting POP-C++ %s [Virtual] Global Services", VERSION);
#else
        LOG_INFO("Starting POP-C++ %s [Standard] Global Services", VERSION);
#endif

/*
 * SECURE VIRTUAL VERSION
 */
#ifdef POPC_SECURE_VIRTUAL
        VirtSecurePOPCSearchNode psn(challenge, daemon);
        LOG_INFO("[POP-C++ Runtime] VSPSN Started [%s]", psn.GetAccessPoint().GetAccessString().c_str());

        // Create the VPSM
        VirtualPOPCSecurityManager psm(challenge, daemon);
        LOG_INFO("[POP-C++ Runtime] VPSM Started [%s]", psm.GetAccessPoint().GetAccessString().c_str());

        // Give reference to other services
        psm.setPSNRef(psn.GetAccessPoint());
        psn.setPSMRef(psm.GetAccessPoint());

        // Init the SSH mode on the VPSM
        psm.initSSHMode();

/*
 * VIRTUAL VERSION
 */
#elif defined POPC_VIRTUAL
        // Create the VPSN
        VirtualPOPCSearchNode psn(challenge, daemon);
        LOG_INFO("[POP-C++ Runtime] VPSN Started [%s]", psn.GetAccessPoint().GetAccessString());

/*
 * SECURE VERSION
 */
#elif defined POPC_SECURE
        // Create the PSM
        POPCSecurityManager psm(challenge, daemon);
        LOG_INFO("[POP-C++ Runtime] PSM created [%s]", psm.GetAccessPoint().GetAccessString());

        // Create the SPSN
        SecurePOPCSearchNode psn(challenge, daemon);
        LOG_INFO("[POP-C++ Runtime] SPSN [%s]", psn.GetAccessPoint().GetAccessString());

        // Give references to other services
        psm.setPSNRef(psn.GetAccessPoint());
        psn.setPSMRef(psm.GetAccessPoint());

        // Init the ssh secure mode on the PSM
        psm.initSSHMode();
#else
        /*
         * STANDARD VERSION
         */

        // Start the POP-C++ Search Node service
        POPCSearchNode psn(challenge, daemon);
        LOG_INFO("[POP-C++ Runtime] PSN Started [%s]", psn.GetAccessPoint().GetAccessString().c_str());
#endif

#if defined POPC_SECURE_VIRTUAL
        // Create the POPCloner
        POPCloner cloner(challenge, daemon);
        LOG_INFO("POPCloner Started [%s]", cloner.GetAccessPoint().GetAccessString());
        // Save the POPCloner access point in the system
        pop_system::popcloner = cloner.GetAccessPoint();

        try {
            // Create the VJobMgr
            VirtSecureJobMgr info(daemon, virtconf, conf, challenge, host, psn.GetAccessPoint(),
                                  cloner.GetAccessPoint(), psm.GetAccessPoint());
            LOG_INFO("VSJM created [%s]", info.GetAccessPoint().GetAccessString());
            psm.setJobMgrRef(info.GetAccessPoint());
        } catch (std::exception& e) {
            LOG_WARNING("Error: Need to stop VSPSN, VPSM and POPCloner: %s", e.what());
            // Stop the created PSN
            if (!psn.Stop(challenge)) {
                LOG_WARNING("Bad challenge string. Cannot stop VSPSN ...");
            } else {
                LOG_INFO("VSPSN stopped successfully!");
            }
            // Stop the created PSM
            if (!psm.Stop(challenge)) {
                LOG_WARNING("Bad challenge string. Cannot stop VPSM ...");
            } else {
                LOG_INFO("VPSM stopped successfully!");
            }
            // Stop the created POPCloner
            if (!cloner.Stop(challenge)) {
                LOG_WARNING("Bad challenge string. Cannot stop POPCloner ...");
            } else {
                LOG_INFO("POPCloner stopped successfully!");
            }
        }
#elif defined POPC_VIRTUAL
        // Create the POPCloner
        POPCloner cloner(challenge, daemon);
        LOG_INFO("POPCloner Started [%s]", cloner.GetAccessPoint().GetAccessString());
        // Save the POPCloner access point in the system
        pop_system::popcloner = cloner.GetAccessPoint();

        try {
            // Create the VJobMgr
            pop_accesspoint empty;
            VirtualJobMgr info(daemon, virtconf, conf, challenge, host, psn.GetAccessPoint(), cloner.GetAccessPoint(),
                               empty);
            LOG_INFO("VJM created [%s]", info.GetAccessPoint().GetAccessString());
        } catch (std::exception& e) {
            LOG_ERROR("Need to stop VPSN and POPCloner: %s", e.what());
            // Stop the created PSN
            if (!psn.Stop(challenge)) {
                LOG_WARNING("Bad challenge string. Cannot stop VPSN ...");
            } else {
                LOG_INFO("VPSN stopped successfully!");
            }
            // Stop the created POPCloner
            if (!cloner.Stop(challenge)) {
                LOG_WARNING("Bad challenge string. Cannot stop POPCloner ...");
            } else {
                LOG_INFO("POPCloner stopped successfully!");
            }
        }
#elif defined POPC_SECURE
        try {
            // Create the SJobMgr
            SecureJobMgr info(daemon, conf, challenge, host, psn.GetAccessPoint(), psm.GetAccessPoint());
            LOG_INFO("SJM created [%s]", info.GetAccessPoint().GetAccessString());
            psm.setJobMgrRef(info.GetAccessPoint());
        } catch (std::exception& e) {
            LOG_ERROR("Need to stop SPSN and PSM: %s", e.what());
            // Stop the created PSN
            if (!psn.Stop(challenge)) {
                LOG_ERROR("Bad challenge string. Cannot stop SPSN ...");
            } else {
                LOG_INFO("SPSN stopped successfully!");
            }
            // Stop the created PSM
            if (!psm.Stop(challenge)) {
                LOG_WARNING("Bad challenge string. Cannot stop PSM ...");
            } else {
                LOG_INFO("SPSN stopped successfully!");
            }
        }
#else
        try {
            // Create the base JobMgr
            pop_accesspoint empty;
            psn.GetAccessPoint();
            JobMgr info(daemon, conf, challenge, host, psn.GetAccessPoint(), empty);
            LOG_INFO("[POP-C++ Runtime] JM created [%s]", info.GetAccessPoint().GetAccessString().c_str());

            // Start the POPFile manager if no option is specified
            /** TO BE REMOVE FOR 2.5 BUT KEEP FOR 3.0
             if(popfile_service){
                POPFileManager pfm(challenge, daemon, hostpfm);
             LOG_INFO("[POP-C++ Runtime] PFM Started [%s]", pfm.GetAccessPoint().GetAccessString());
                 pfm.setPSNAccessPoint(psn.GetAccessPoint());
                pfm.getNeighborsFromPSN();
            } */
        } catch (std::exception& e) {
            LOG_WARNING("Error: Need to stop PSN: %s", e.what());
            if (!psn.Stop(challenge)) {
                LOG_WARNING("Bad challenge string. Cannot stop PSN ...");
            } else {
                LOG_INFO("PSN stopped successfully!");
            }
        }
#endif
        if (daemon) {
            return 0;
        }
    } catch (std::exception& e) {
        LOG_ERROR("Exception while launching job manager: %s", e.what());
    }
    return 0;
}
