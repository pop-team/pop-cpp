/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of network access point of parallel objects.
 *
 *
 */

// Deeply need refactoring: POPC_AccessPoint instead of pop_accesspoint

#include "pop_intface.h"
//#include <stdio.h>
//#include <string.h>
//#include <stdlib.h>

#include "pop_accesspoint.h"
#include "pop_utils.h"

/**
 * Accesspoint constructor
 */
pop_accesspoint::pop_accesspoint() {
    _security = NONSECURE;
    _service = false;
    _noaddref = false;
}

/**
 * Accesspoint copy constructor
 */
pop_accesspoint::pop_accesspoint(const pop_accesspoint& p) {
    endpoint = "";
    SetAccessString(p.GetAccessString());
    if (p.IsSecure()) {
        _security = SECURE;
    } else {
        _security = NONSECURE;
    }
    if (p.IsService()) {
        SetAsService();
    }
    _noaddref = GetNoAddRef();
}

/**
 * Accesspoint destructor
 */
pop_accesspoint::~pop_accesspoint() {
}

/**
 * Set the different access in a string format. Each access is separated by a whit space.
 * @param hostport  Access string to set as mai access
 */
void pop_accesspoint::SetAccessString(const std::string& hostport) {
    endpoint = hostport;
}
const std::string& pop_accesspoint::GetAccessString() const {
    return endpoint;
}

bool pop_accesspoint::IsEmpty() const {
    return (endpoint == "");
}

bool pop_accesspoint::operator==(const pop_accesspoint& p) const {
    return endpoint == p.GetAccessString();
}

pop_accesspoint& pop_accesspoint::operator=(const pop_accesspoint& p) {
    SetAccessString(p.GetAccessString());
    if (p.IsSecure()) {
        SetSecure();
    }
    if (p.IsService()) {
        SetAsService();
    }
    return *this;
}

/**
 * ViSaG : clementval
 * Check if the access point is in secure mode
 * @return TRUE if the access point is in secure mode
 */
bool pop_accesspoint::IsSecure() const {
    if (_security == SECURE) {
        return true;
    }
    return false;
}

/**
 * ViSaG : clementval
 * Set the access point in a secure mode
 */
void pop_accesspoint::SetSecure() {
    _security = SECURE;
}

/**
 * ViSaG : clementval
 * Return true is the accesspoint is reffered to a service
 * @return TRUE if the parallel object pointed by the access point is a service
 */
bool pop_accesspoint::IsService() const {
    return _service;
}

/**
 * Get the boolean value that says if the creation of an interface with this access point must increment the internal
 * counter
 */
bool pop_accesspoint::GetNoAddRef() const {
    return _noaddref;
}

/**
 * ViSaG : clementval
 * Set the variable _service to TRUE
 */
void pop_accesspoint::SetAsService() {
    _service = true;
}

void pop_accesspoint::SetNoAddRef() {
    _noaddref = true;
}

void pop_accesspoint::Serialize(pop_buffer& buf, bool pack) {
    if (pack) {
        std::string s(endpoint);
        buf.Push("url", "std::string", 1);
        buf.Pack(&s, 1);
        buf.Pop();

        int sec = _security;
        buf.Push("_security", "int", 1);
        buf.Pack(&sec, 1);
        buf.Pop();

        bool serv = _service;
        buf.Push("_service", "bool", 1);
        buf.Pack(&serv, 1);
        buf.Pop();

        bool noadd = _noaddref;
        buf.Push("_noaddref", "bool", 1);
        buf.Pack(&noadd, 1);
        buf.Pop();
    } else {
        std::string s;
        buf.Push("url", "std::string", 1);
        buf.UnPack(&s, 1);
        buf.Pop();
        SetAccessString(s.c_str());

        int sec;
        buf.Push("_security", "int", 1);
        buf.UnPack(&sec, 1);
        buf.Pop();
        if (sec == SECURE) {
            SetSecure();
        }

        bool serv;
        buf.Push("_service", "bool", 1);
        buf.UnPack(&serv, 1);
        buf.Pop();
        if (serv) {
            SetAsService();
        }

        bool noadd;
        buf.Push("_noaddref", "bool", 1);
        buf.UnPack(&noadd, 1);
        buf.Pop();
        if (noadd) {
            SetNoAddRef();
        }
    }
}
