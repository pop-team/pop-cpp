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

paroc_exception::paroc_exception() {
    errcode=0;
}
paroc_exception::paroc_exception(int code) {
    errcode=code;
}

paroc_exception & paroc_exception::operator =(paroc_exception &e) {
    errcode=e.Code();
    info=e.Extra();
    return *this;
}
const POPString paroc_exception::Extra()const {
    return info;
}

void paroc_exception::SetExtra(const char* str) {
    info=str;
}

int paroc_exception::Code()const {
    return errcode;
}

void paroc_exception::paroc_throw(int code, const char *reason) {
    paroc_exception *e=new paroc_exception(code);
    if(reason!=NULL) {
        e->SetExtra(reason);
    }
    throw e;
}

void paroc_exception::paroc_throw(const char *reason) {
    paroc_exception *e=new paroc_exception(UNKNOWN_EXCEPTION);
    if(reason!=NULL) {
        e->SetExtra(reason);
    }
    throw e;
}

void paroc_exception::paroc_throw_errno(const char *reason) {
    paroc_exception *e=new paroc_exception(errno);
    if(reason!=NULL) {
        e->SetExtra(reason);
    }
    throw e;
}

paroc_exception *paroc_exception::create(int code, const char *reason) {
    paroc_exception *e=new paroc_exception(code);
    if(reason!=NULL) {
        e->SetExtra(reason);
    }
    return e;
}

const char* paroc_exception::what() const throw() {
    errno=Code();
    return (const char*)info;
}

void paroc_exception::Print()const {
    paroc_system::perror(this);
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
