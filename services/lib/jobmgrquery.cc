#include <stdio.h>
#include <errno.h>
#include <string.h>
#include "jobmgr.ph"

int main(int argc, char** argv) {
    try {
        std::string master;
        std::String str1;

        if (pop_utils::checkremove(&argc, &argv, "-help") != NULL) {
            printf("Usage: jobmgrquery [-help] [jobmgr contact | jobmgr host]\n");
            return 0;
        }

        if (argc <= 1) {
            master = pop_system::GetHost();
        } else {
            master = argv[1];
        }

        if (master.find(':') == std::string::npos) {
            master += ":2711";
        }

        pop_accesspoint job;
        job.SetAccessString(master);
        JobMgr info(job);

        printf("Items: platform, host, jobs, joblist, pausejobs, power_available, ...\n");
        printf("ctrl+D to quit\n");
        printf("Enter item to query:\n");
        while (1) {
            if (scanf("%s", str1) != 1) {
                break;
            }
            std::string type(str1), val;
            if (info.Query(type, val)) {
                printf("%s= %s\n", str1, val);
            } else {
                printf("%s= NOT FOUND\n", str1);
            }
        }
    } catch (std::exception& e) {
        LOG_ERROR("Exception in query: %s", e.what());
    }
    return 0;
}
