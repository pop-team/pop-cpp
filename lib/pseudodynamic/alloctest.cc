/**
 * File : alloctest.cc
 * Author : Tuan Anh Nguyen
 * Description : Batch creation mechanism of parallel objects (Test)
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 * P.Kuonen     18.9.2012       Add "POP-C++ error" in error messages (PEKA)
 */

#include <stdio.h>
#include <string.h>
#include "jobmgr.ph"
#include "paroc_array.h"

int main(int argc, char** argv) {
    int howmany;
    if (argc < 4 || sscanf(argv[3], "%d", &howmany) != 1 || howmany <= 0) {
        printf("Usage: alloctest jobmgrcontact object howmany\n");
        return 1;
    }

    std::string objname = argv[2];
    pop_accesspoint job;
    job.SetAccessString(argv[1]);
    paroc_list<pop_accesspoint> resources;
    paroc_list<int> reserve;

    try {
        JobMgr jobmgr(job);
        char buf[1024];
        pop_od* od = new pop_od;
        LOG_INFO("Enter an OD (name values)");
        while (fgets(buf, 1023, stdin) != NULL) {
            if (strncmp(buf, "done", 4) == 0) {
                paroc_array<pop_accesspoint> jobcontacts(howmany);
                paroc_array<int> reserveIDs(howmany);
                paroc_array<float> fitness(howmany);

                LOG_INFO("Do resource allocation now...");
                int requestInfo[3];
                int iptrace[MAX_HOPS];

                for (int i = 0; i < howmany; i++) {
                    fitness[i] = 0;
                }

                if (jobmgr.AllocResource(pop_system::appservice, objname, *od, howmany, fitness, jobcontacts,
                                         reserveIDs, requestInfo, iptrace, 0)) {
                    for (int i = 0; i < howmany; i++) {
                        LOG_INFO("#%d:%s (%d)\n", i + 1, jobcontacts[i].GetAccessString(), reserveIDs[i]);
                        resources.AddTailNew() = jobcontacts[i];
                        reserve.AddTail(reserveIDs[i]);
                    }
                } else {
                    LOG_ERROR("Alloc fail");
                }
                delete od;
                od = new pop_od;
                LOG_DEBUG("Enter next OD");
                continue;
            }
            int v1, v2 = -1;
            char name[256];
            int t = sscanf(buf, "%s %d %d", name, &v1, &v2);
            if (t < 2) {
                LOG_ERROR("POP-C++ Error: Bad OD value");
                continue;
            }
            if (strcmp(name, "power") == 0) {
                od->power(v1, v2);
            } else if (strcmp(name, "memory") == 0) {
                od->memory(v1, v2);
            } else if (strcmp(name, "np") == 0) {
                howmany = v1;
            } else {
                LOG_ERROR("POP-C++ Error: Unkown OD name");
            }
        }
        POSITION pos = resources.GetHeadPosition();
        POSITION pos1 = reserve.GetHeadPosition();
        while (pos != NULL) {
            pop_accesspoint& t = resources.GetNext(pos);
            int& r = reserve.GetNext(pos1);
            JobMgr tmp(t);
            tmp.CancelReservation(&r, 1);
        }
        resources.RemoveAll();
    } catch (std::exception& e) {
        LOG_WARNING("Exception in alloctest: %s", e.what());
        return 1;
    }

    return 0;
}
