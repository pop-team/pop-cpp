/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Regroups commonly used functions.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_CommonTools instead of pop_utils
 */

#include "popc_intface.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include "pop_utils.h"

char *pop_utils::checkremove(int *argc, char ***argv, const char *opt) {
    int i=0;
    int n=strlen(opt);
    char* ret=nullptr;
    while(i<*argc) {
        if(strncmp((*argv)[i],opt,n)==0) {
            ret=(*argv)[i]+n;
            for(int j=i; j<*argc-1; j++) {
                (*argv)[j]=(*argv)[j+1];
            }
            (*argc)--;
        } else {
            i++;
        }
    }
    return ret;
}

bool pop_utils::check_remove(int *argc, char ***argv, const char *opt) {
    return checkremove(argc, argv, opt);
}

bool pop_utils::isEqual(const char *s1, const char *s2) {
    if(s1==s2) {
        return true;
    }
    if(s1==nullptr || s2==nullptr) {
        return false;
    }
    while(*s1!=0 && *s2!=0) {
        if(*s1!=*s2) {
            return false;
        }
        s1++;
        s2++;
    }
    return (*s1==*s2);
}

bool pop_utils::isncaseEqual(const std::string& x_s1, const std::string& x_s2) {
    if(&x_s1==&x_s2) {
        return true;
    }
    if(x_s1.empty() || x_s2.empty()) {
        return false;
    }
    const char* s1 = x_s1.c_str();
    const char* s2 = x_s2.c_str();
    while(*s1!=0 && *s2!=0) {
        char ch1=*s1;
        char ch2=*s2;
        if(ch1>='a' && ch1<='z') {
            ch1-=32;
        }
        if(ch2>='a' && ch2 <='z') {
            ch2-=32;
        }
        if(ch1!=ch2) {
            return false;
        }
        s1++;
        s2++;
    }
    return (*s1==*s2);
}

bool pop_utils::MatchWildcard(const std::string& str, const std::string& wildcard) {
    if(str==wildcard) {
        return true;
    }
    if(str=="" || wildcard=="") {
        return false;
    }
    const char* pstr = str.c_str();
    const char* pwil = wildcard.c_str();
    while(*pstr!=0 && (*pstr==*pwil || *pwil=='?')) {
        if(*pwil=='*') {
            break;
        }
        pstr++;
        pwil++;
    }

    if(*pwil==0) {
        return (*pstr==0);
    }
    if(*pwil!='*') {
        return false;
    }

    while(*pwil=='*') {
        pwil++;
    }
    if(*pwil==0) {
        return true;
    }

    const char *t=pstr;

    while(*t!=0) {
        if(*t==*pwil || *pwil=='?') {
            if(MatchWildcard(t+1,pwil+1)) {
                return true;
            }
        }
        t++;
    }
    return false;

}

std::string pop_utils::FindAbsolutePath(const std::string& fname) {
    if(fname.empty())
        return "";
    if(fname.at(0)=='/')
        return fname;

    unsigned pos = fname.find_last_of('/');
    char dir[1024];

    if(pos >= fname.size()) {
        // not found
        if(popc_getcwd(dir,1024)==nullptr) {
            *dir=0;
        }
        std::string s(dir);
        return s + "/" + fname;
    }
    char olddir[1024];
    popc_getcwd(olddir,1024);
    popc_chdir(fname.substr(0,pos-1).c_str());
    if(popc_getcwd(dir,1024)==nullptr) {
        *dir=0;
    }
    popc_chdir(olddir);
    std::string s1(dir);
    return s1 + "/" + fname.substr(pos+1);
}



#ifdef _POPC_
#include "pop_system.h"

bool pop_utils::SameContact(const std::string& _contact1, const std::string& _contact2) {
    const char* contact1 = _contact1.c_str();
    const char* contact2 = _contact2.c_str();
    if(contact1==contact2) {
        return true;
    }
    if(contact1==nullptr || contact2==nullptr) {
        return false;
    }
    if(strstr(contact1, contact2)!=nullptr || strstr(contact2, contact1)!=nullptr) {
        return true;
    }

    char *ptr;

    std::vector<std::string> tokens;
    popc_tokenize_r(tokens,contact2," \n\r\t");
    for(auto token : tokens) {
        if(strstr(contact1,token.c_str())!=nullptr) {
            return true;
        }
    }
    return false;
}

//Return true if the destination is remote
bool pop_utils::IsRemoteDest(const char *dest) {
    std::string destination(dest);

    char host[256];
    popc_gethostname(host, 256);

    //Three string to test with
    std::string _host(host);

    size_t c1=destination.find("127.0.0.1");
    size_t c2=destination.find(pop_system::GetIP()); // local ip
    size_t c3=destination.find(_host);
    //If one of the 3 strings above is find in the destination, this is a local destination
    if(c1==std::string::npos && c2==std::string::npos && c3==std::string::npos) {
        return true;
    }
    return false;
}



//Get the port defined in a URL
int pop_utils::GetPortFromURL(const char *url) {
    std::string surl(url);
    size_t pos;
    pos=surl.rfind(":");
    std::string port=surl.substr(pos+1, std::string::npos);
    int p = atoi(port.c_str());
    return p;
}

//Get the IP address defined in a URL
const char* pop_utils::GetIPFromURL(const char *url) {
    std::string surl(url);
    size_t pos1, pos2;
    pos1=surl.find("://");
    pos2=surl.rfind(":");
    std::string ip;
    if(pos1!=std::string::npos) {
        ip=surl.substr(pos1+3, pos2-pos1-3);
    } else {
        ip=surl.substr(0, pos2);
    }
    return ip.c_str();
}

//Get the current user
const char* pop_utils::GetCurrentUser() {
#ifndef __WIN32__
    return getlogin();
#else
    char *username;
    DWORD i = 256;
    DWORD* temp = &i;
    GetUserName(username, temp);
    return username;
#endif
}

std::string pop_utils::MakeContact(const char *host, int port) {
    if(port<=0) {
        return host;
    }
    char tmpcontact[256];
    snprintf(tmpcontact,sizeof(tmpcontact),"%s:%d",host,port);
    return std::string(tmpcontact);
}


#include "appservice.ph"
int rprintf(const char *format,...) {
    char str[1024];

    va_list ap;
    va_start(ap, format);
    vsnprintf(str,sizeof(str), format, ap);
    va_end(ap);
    if(pop_system::appservice.IsEmpty()) {
        //At this point, we arrive from an object that has no appservice, namely a local object (RemoteLog for instance)
        //In which case, a printf can be done directly on the console (logging it would add unecessary content to the log)
        fprintf(stdout, "%s", str);
        fflush(stdout);
        // LOG_INFO("CANNOT LOG THIS: %s",str); // TODO: Discuss with bw: why no logging in /tmp ?
        return 0;
    }
    try {
        // TODO LW: Each time we call rprintf a new connection to the remote is created. Can we be more efficient ?
        RemoteLog log(pop_system::appservice);
        std::string msg(str);
        log.Log(msg);
    } catch(std::exception e) {
        LOG_ERROR("Exception in rprintf: %s", e.what());
        LOG_INFO("%s",str);
        fflush(stdout);
        return 0;
    }
    return 1;
}

int pop_utils::InitCodeService(char *fileconf, AppCoreService *s) {
    if(s==nullptr || fileconf==nullptr) {
        return 0;
    }

    FILE *f=fopen(fileconf,"r");
    char objname[256],arch[256], codefile[256];
    char line[256];
    char sep[]=" \n\t";

    if(f==nullptr) {
        return 0;
    }
    try {
        while(!feof(f)) {
            if(fgets(line,256,f)!=nullptr) {

                int last=strlen(line)-1;
                while(last>=0 && isspace(line[last])) {
                    line[last]=0;
                    last--;
                }
                if(last==0) {
                    continue;
                }

                char *tmp=strtok(line,sep);
                if(tmp==nullptr) {
                    continue;
                }
                strcpy(objname,tmp);
                tmp=strtok(nullptr,sep);
                if(tmp==nullptr) {
                    continue;
                }
                strcpy(arch,tmp);
                tmp+=strlen(tmp)+1;
                if(*tmp==0) {
                    continue;
                }
                strcpy(codefile,tmp);

                s->RegisterCode(objname,arch,codefile);
            }
        }
    } catch(std::exception &e) {
        fclose(f);
        LOG_WARNING("Exception while registring code: %s", e.what());
        return 0;
    }
    fclose(f);
    return 1;
}

/**
 * ViSaG : clementval
 * Check if the given string is a IP v4 address
 * @param
 *
 */
bool pop_utils::isIPv4Address(std::string ip) {

    //check max size
    if(ip.size() > 15) {
        return false;
    }

    //check if the IP address has three dots
    size_t dot1, dot2, dot3;
    dot1 = ip.find(".");
    dot2 = ip.find(".", dot1+1);
    dot3 = ip.find(".", dot2+1);

    if(dot1 == std::string::npos || dot2 == std::string::npos || dot3 == std::string::npos) {
        return false;
    }

    //check if char are number
    for(size_t i=0; i<ip.length(); i++) {
        char c = ip.at(i);
        if((c != '.') && !isdigit(c)) {
            return false;
        }
    }


    return true;
}

/**
 * ViSaG : clementval
 * Check is a value is only letter and number
 * @param
 * @retrun
 */

bool pop_utils::isValidName(std::string checked) {
    for(size_t i=0; i<checked.length(); i++) {
        char c = checked.at(i);
        if((c != '_') && !isdigit(c) && !isalpha(c)) {
            return false;
        }
    }
    return true;
}

#else
// Note LWK: This function is added as a hack to allow compilation in pseudodynamic
// TODO LWK: To fix this cleanly we need to add popc objects to pseudodynamic lib
int rprintf(const char *format,...) {
    return printf("%s", format);
}

#endif
