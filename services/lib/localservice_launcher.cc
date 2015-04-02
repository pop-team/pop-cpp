#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pop_accesspoint.h"
#include "appservice.ph"

void Usage() {
    printf("Usage: localservice_launcher  [-servicepoint=<host>[:port]]  <start [options]> |  <stop>\n\tOptions:\n\t  [-challenge=<string>] [-code=<appservice codefile>] [-conf=<config file>] [-proxy=<POP-C++ proxy>] [-test] [-out=<file> (default:stdout)]\n");
    exit(-1);
}

int main(int argc, char **argv) {
    int port;
    char objcode[256], host[256];
    std::string challenge;

    char *tmp;
    bool stop=(paroc_utils::checkremove(&argc,&argv,"stop")!=NULL);

    if(!stop && paroc_utils::checkremove(&argc,&argv,"start")==NULL) {
        Usage();
    }

    tmp=paroc_utils::checkremove(&argc,&argv,"-challenge=");
    if(tmp!=NULL) {
        challenge=tmp;
    }

    if((tmp=paroc_utils::checkremove(&argc,&argv,"-servicepoint="))==NULL) {
        if(stop) {
            LOG_WARNING("Local service point to stop is missing");
            Usage();
        } else {
            snprintf(host,sizeof(host),"%s:2711",pop_system::GetHost().c_str());
        }
    } else {
        strcpy(host,tmp);
    }

    try {
        if(stop) {
            pop_accesspoint pt;
            pt.SetAccessString(host);
            LOG_INFO("Connecting to %s..." ,host);
            AppCoreService mgr(pt);
            if(mgr.Stop(challenge)) {
                LOG_INFO("...Stopped");
            } else {
                LOG_WARNING("...fail to stop. Please check the challenge string!");
            }
            return 0;
        }

        if((tmp=paroc_utils::checkremove(&argc,&argv,"-code="))==NULL) {
            if((tmp=getenv("POPC_LOCATION"))==NULL) {
                LOG_ERROR("local service code file is not specified");
                Usage();
            }
            snprintf(objcode,sizeof(objcode),"%s/services/appservice",tmp);
        } else {
            strcpy(objcode,tmp);
        }

        if((tmp=paroc_utils::checkremove(&argc,&argv,"-proxy="))!=NULL) {
            strcat(objcode," -proxy=");
            strcat(objcode,tmp);
        }

        char *outfile=paroc_utils::checkremove(&argc,&argv,"-out=");
        FILE *f=(outfile!=NULL)? fopen(outfile,"w+t") : NULL;
        if(f==NULL && outfile!=NULL) {
            perror("Open file to store the service access point failed");
            return 1;
        }

        AppCoreService info(challenge, true, objcode);

        char *conf=paroc_utils::checkremove(&argc,&argv,"-conf=");
        if(conf!=NULL) {
            paroc_utils::InitCodeService(conf,&info);
        }

        //print out the contact string....
        if(f==NULL) {
            LOG_INFO("%s",info.GetAccessPoint().GetAccessString().c_str());
        } else {
            fprintf(f,"%s",info.GetAccessPoint().GetAccessString().c_str());
            fclose(f);
        }

    } catch(int e) {
        errno=e;
        LOG_ERROR("Exception in localservice_launcher");
        return 1;
    } catch(std::exception &e) {
        LOG_ERROR("Exception in localservice_launcher: %s", e.what());
        return 1;
    }
    return 0;
}
