/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of the POP-C++ runtime exception class.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_Exception instead of paroc_exception
 */

#include <string.h>
#include <errno.h>

#include "paroc_exception.h"
#include "paroc_system.h"
#include "popc_logger.h"

const char *paroc_exception::paroc_errstr[17]= { // Error number: 1000 + ...
    "Out of resource",                           // 1
    "Fail to bind to the remote object broker",  // 2
    "Mismatch remote method id",                 // 3
    "Can not access code service",               // 4
    "Object allocation failed",                  // 5
    "No parallel object executable",             // 6
    "Bad paroc package format",                  // 7
    "Local application service failed",          // 8
    "Job Manager service failed",                // 9
    "Execution of object code failed",           // 10
    "Bad binding reply",                         // 11
    "No support protocol",                       // 12
    "No support data encoding",                  // 13
    "Standard exception",                        // 14
    "Acknowledgement not received",              // 15
    "Network configuration error",               // 16
    "Unknown exception"                          // 17
};



paroc_exception::paroc_exception() {
    errcode=0;
}

paroc_exception::paroc_exception(int code) {
    errcode=code;
    if(code>USER_DEFINE_ERROR && code<USER_DEFINE_LASTERROR && code != UNKNOWN_EXCEPTION) {
        info = paroc_errstr[code-USER_DEFINE_ERROR-1];
    } else if(code>=USER_DEFINE_LASTERROR) {
        LOG_ERROR("Error code is too large: %d", code);
    } else {
        info = "System error(";
        info += strerror(code);
        info += ")";
    }
}

paroc_exception & paroc_exception::operator =(paroc_exception &e) {
    errcode=e.Code();
    info=e.Info();
    return *this;
}

const POPString paroc_exception::Info()const {
    return info;
}

void paroc_exception::AddInfo(const char* str) {
    if(info.Length() != 0)
	    info += ": ";
    info += str;
}

int paroc_exception::Code()const {
    return errcode;
}

void paroc_exception::paroc_throw(int code, const char *reason1, const char *reason2) {
    paroc_exception e(code);
    if(reason1!=NULL) {
        e.AddInfo(reason1);
    }
    if(reason2!=NULL) {
        e.AddInfo(reason2);
    }
    throw e;
}

void paroc_exception::paroc_throw(const char *reason1, const char *reason2) {
    paroc_exception e(UNKNOWN_EXCEPTION);
    if(reason1!=NULL) {
        e.AddInfo(reason1);
    }
    if(reason2!=NULL) {
        e.AddInfo(reason2);
    }
    throw e;
}

const char* paroc_exception::what() const throw() {
    errno=Code();
    return (const char*)info;
}


void paroc_exception::Serialize(paroc_buffer &buf, bool pack) {
    if(pack) {
        buf.Push("code","int",1);
        buf.Pack(&errcode,1);
        buf.Pop();

        buf.Push("info","POPString",1);
        buf.Pack(&info,1);
        buf.Pop();
    } else {
        buf.Push("code","int",1);
        buf.UnPack(&errcode,1);
        buf.Pop();

        buf.Push("info","POPString",1);
        buf.UnPack(&info,1);
        buf.Pop();
    }
}


///
/// perror is the old way to manage errors. It simply prints an error message to stderr
///
void paroc_exception::perror(const char *msg) {
    LOG_ERROR("paroc_system::perror : %d",errno);
    if(errno>USER_DEFINE_ERROR && errno<USER_DEFINE_LASTERROR) {
        if(msg==NULL) {
            msg="POP-C++ Error";
        }
        LOG_ERROR("%s: %s (errno %d)",msg,paroc_errstr[errno-USER_DEFINE_ERROR-1],errno);
    } else if(errno>USER_DEFINE_LASTERROR) {
        LOG_ERROR("%s: Unknown error (errno %d)",msg, errno);
    } else {
        ::perror(msg);
    }
}
