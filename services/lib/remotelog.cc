/**
 * File : remotelog.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of the remote log service
 * Creation date : -
 *
 * Modifications :
 * Authors      Date            Comment
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include "remotelog.ph"
#include "appservice.ph"

RemoteLog::RemoteLog(const POPString &challenge): paroc_service_base(challenge) {
}
RemoteLog::~RemoteLog() {
}

void RemoteLog::Log(const POPString &info) {
    POPString prt=info;
    //By doing a fprintf we avoid to go through rprintf (it'll be a bit faster and easier to understand)
    fprintf(stdout, "%s",prt.GetString());
    fflush(stdout);
}

/**
 * Method used to write remote log into a specific file
 * @param info String to write into the file.
 */
void RemoteLog::LogPJ(const POPString &appID, const POPString &info) {
    POPString prt=info;
    POPString id=appID;
    std::string filename("/tmp/popjava_logremote_");
    filename.append(id.GetString());
    std::ofstream logfile;
    logfile.open(filename.c_str(), std::ios::app);
    if(logfile.is_open()) {
        logfile << prt.GetString();
        logfile.close();
    }
}
