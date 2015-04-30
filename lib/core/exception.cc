/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
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
    POPC_Exception instead of pop_exception
 */

#include <string.h>
#include <errno.h>

#include "pop_exception.h"
#include "pop_system.h"
#include "popc_logger.h"

const char* pop_exception::paroc_errstr[17] = {  // Error number: 1000 + ...
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

pop_exception::pop_exception(int code) {
    errcode = code;
    if (code == UNKNOWN_EXCEPTION) {
        ;  // Do nothing
    } else if (code >= USER_DEFINE_LASTERROR) {
        LOG_ERROR("Error code is too large: %d", code);
    } else if (code > USER_DEFINE_ERROR) {
        info = paroc_errstr[code - USER_DEFINE_ERROR - 1];
    } else {
        info = "System error(";
        info += strerror(code);
        info += ")";
    }
}

pop_exception::pop_exception(int code, const std::string& reason1, const std::string& reason2) : pop_exception(code) {
    if (!reason1.empty()) {
        AddInfo(reason1);
    }
    if (!reason2.empty()) {
        AddInfo(reason2);
    }
}

pop_exception::pop_exception(const std::string& reason1, const std::string& reason2)
    : pop_exception(UNKNOWN_EXCEPTION) {
    if (!reason1.empty()) {
        AddInfo(reason1);
    }
    if (!reason2.empty()) {
        AddInfo(reason2);
    }
}

pop_exception& pop_exception::operator=(pop_exception& e) {
    errcode = e.Code();
    info = e.Info();
    return *this;
}

const std::string& pop_exception::Info() const {
    return info;
}

void pop_exception::AddInfo(const std::string& str) {
    if (!info.empty())
        info += ": ";
    info += str;
}

int pop_exception::Code() const {
    return errcode;
}

void pop_exception::pop_throw(int code, const std::string& reason1, const std::string& reason2) {
    throw pop_exception(code, reason1, reason2);
}

void pop_exception::pop_throw(const std::string& reason1, const std::string& reason2) {
    throw pop_exception(reason1, reason2);
}

const char* pop_exception::what() const throw() {
    errno = Code();
    return info.c_str();
}

void pop_exception::Serialize(pop_buffer& buf, bool pack) {
    if (pack) {
        buf.Push("code", "int", 1);
        buf.Pack(&errcode, 1);
        buf.Pop();

        buf.Push("info", "std::string", 1);
        buf.Pack(&info, 1);
        buf.Pop();
    } else {
        buf.Push("code", "int", 1);
        buf.UnPack(&errcode, 1);
        buf.Pop();

        buf.Push("info", "std::string", 1);
        buf.UnPack(&info, 1);
        buf.Pop();
    }
}

///
/// perror is the old way to manage errors. It simply prints an error message to stderr
///
void pop_exception::perror(const std::string& msg) {
    LOG_ERROR("pop_system::perror : %d", errno);
    if (errno > USER_DEFINE_ERROR && errno < USER_DEFINE_LASTERROR) {
        if (!msg.empty())
            LOG_ERROR("POP-C++ Error: %s (errno %d)", paroc_errstr[errno - USER_DEFINE_ERROR - 1], errno);
        else
            LOG_ERROR("%s: %s (errno %d)", msg.c_str(), paroc_errstr[errno - USER_DEFINE_ERROR - 1], errno);
    } else if (errno > USER_DEFINE_LASTERROR) {
        LOG_ERROR("%s: Unknown error (errno %d)", msg.c_str(), errno);
    } else {
        ::perror(msg.c_str());
    }
}
