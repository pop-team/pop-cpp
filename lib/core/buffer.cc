/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of message buffer base class.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_Buffer instead of pop_buffer
    POPC_MessageHeader instead of pop_message_header (put implementation in a separate file)
 */

#include <cstring>
#include <cstdlib>
#include <vector>

#include "pop_interface.h"
#include "pop_buffer.h"
#include "pop_system.h"
#include "pop_exception.h"
#include "popc_logger.h"

// Message header

pop_message_header::pop_message_header(int classid, int methodid, int semantics, const char* metname) {
    type = TYPE_REQUEST;
    id[0] = classid;
    id[1] = methodid;
    id[2] = semantics;
    methodname = metname;
}

pop_message_header::pop_message_header(const char* metname) {
    type = TYPE_RESPONSE;
    methodname = metname;
}

pop_message_header::pop_message_header(int exceptioncode, const char* metname) {
    type = TYPE_EXCEPTION;
    methodname = metname;
    SetExceptionCode(exceptioncode);
}

pop_message_header::pop_message_header() {
    type = -1;
    methodname = nullptr;
}

void pop_message_header::operator=(const pop_message_header& dat) {
    if (&dat == this) {
        return;
    }
    type = dat.GetType();
    SetMethodName(dat.GetMethodName());
    switch (type) {
        case TYPE_REQUEST:
            id[0] = dat.GetClassID();
            id[1] = dat.GetMethodID();
            id[2] = dat.GetSemantics();
            break;
        case TYPE_EXCEPTION:
            exception = dat.GetExceptionCode();
            break;
    }
}

// Message envelop

pop_buffer::pop_buffer() {
}

pop_buffer::~pop_buffer() {
}

void pop_buffer::SetHeader(const pop_message_header& data) {
    header = data;
}

const pop_message_header& pop_buffer::GetHeader() const {
    return header;
}

void pop_buffer::Push(const char* paramname, const char* paramtype, int nelem) {
    (void)paramname;
    (void)paramtype;
    (void)nelem;
    // LOG_DEBUG("push %s of type %s", paramname, paramtype);
}

void pop_buffer::Pop() {
}

void pop_buffer::Pack(const std::string* list, int n) {
    if (n <= 0 || list == nullptr) {
        return;
    }
    for (int i = 0; i < n; i++, list++) {
        int len = list->length() + 1;
        Pack(&len, 1);
        if (len > 0) {
            Pack(list->c_str(), len);
        }
    }
}

void pop_buffer::UnPack(std::string* list, int n) {
    if (n <= 0 || list == nullptr) {
        return;
    }
    std::vector<char> tmpstr;

    for (int i = 0; i < n; i++, list++) {
        int len;
        UnPack(&len, 1);
        if (len > 0) {
            tmpstr.resize(len);
            UnPack(tmpstr.data(), len);
            *list = tmpstr.data();
        } else {
            list->clear();
        }
    }
}

bool pop_buffer::Send(pop_connection* conn) {
    if (conn == nullptr) {
        LOG_ERROR("conn==nullptr");
        return false;
    }
    auto combox = conn->GetCombox();
    return Send(*combox, conn);
}

bool pop_buffer::Recv(pop_connection* conn) {
    if (conn == nullptr) {
        LOG_ERROR("conn==nullptr");
        return false;
    }
    auto combox = conn->GetCombox();
    return Recv(*combox, conn);
}

#define SEND_EXCEPTION(x)                                          \
    pop_message_header tmp(x, except.GetHeader().GetMethodName()); \
    except.Reset();                                                \
    except.SetHeader(tmp);                                         \
    except.Pack(&code, 1);                                         \
    return except.Send(s);

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, int code) {
    SEND_EXCEPTION(EXCEPTION_INT);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, unsigned code) {
    SEND_EXCEPTION(EXCEPTION_UINT);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, long code) {
    SEND_EXCEPTION(EXCEPTION_LONG);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, unsigned long code) {
    SEND_EXCEPTION(EXCEPTION_ULONG);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, short code) {
    SEND_EXCEPTION(EXCEPTION_SHORT);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, unsigned short code) {
    SEND_EXCEPTION(EXCEPTION_USHORT);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, bool code) {
    SEND_EXCEPTION(EXCEPTION_BOOL);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, char code) {
    SEND_EXCEPTION(EXCEPTION_CHAR);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, unsigned char code) {
    SEND_EXCEPTION(EXCEPTION_UCHAR);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, char* code) {
    except.Reset();
    pop_message_header tmp(EXCEPTION_STRING, except.GetHeader().GetMethodName());
    except.SetHeader(tmp);
    int len = (code == nullptr) ? 0 : strlen(code) + 1;
    except.Pack(&len, 1);
    except.Pack(code, len);

    return except.Send(s);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, float code) {
    SEND_EXCEPTION(EXCEPTION_FLOAT);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, double code) {
    SEND_EXCEPTION(EXCEPTION_DOUBLE);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, pop_exception& code) {
    //  SEND_EXCEPTION(EXCEPTION_POPC_STD);
    pop_message_header tmp(EXCEPTION_POPC_STD, except.GetHeader().GetMethodName());
    except.Reset();
    except.SetHeader(tmp);
    code.Serialize(except, true);
    return except.Send(s);
}

bool pop_buffer::SendException(pop_buffer& except, pop_connection* s, pop_interface& code) {
    pop_message_header tmp(EXCEPTION_OBJECT, except.GetHeader().GetMethodName());
    except.Reset();
    except.SetHeader(tmp);
    code.Serialize(except, true);
    return except.Send(s);
}

/// Check if an exception was thrown by the remote method and propagate (if thrown)
void pop_buffer::CheckAndThrow(pop_buffer& except) {
    const pop_message_header& h = except.GetHeader();

    if (h.GetType() != TYPE_EXCEPTION) {
        return;
    }
    int code = h.GetExceptionCode();
    LOG_DEBUG("Exception thrown type=%d", code);
    switch (code) {
        case EXCEPTION_INT: {
            int t;
            except.UnPack(&t, 1);
            throw t;
        }
        case EXCEPTION_UINT: {
            unsigned t;
            except.UnPack(&t, 1);
            throw t;
        }
        case EXCEPTION_LONG: {
            long t;
            except.UnPack(&t, 1);
            throw t;
        }
        case EXCEPTION_ULONG: {
            unsigned long t;
            except.UnPack(&t, 1);
            throw t;
        }

        case EXCEPTION_SHORT: {
            short t;
            except.UnPack(&t, 1);
            throw t;
        }

        case EXCEPTION_USHORT: {
            unsigned short t;
            except.UnPack(&t, 1);
            throw t;
        }
        case EXCEPTION_BOOL: {
            bool t;
            except.UnPack(&t, 1);
            throw t;
        }
        case EXCEPTION_CHAR: {
            char t;
            except.UnPack(&t, 1);
            throw t;
        }
        case EXCEPTION_UCHAR: {
            unsigned char t;
            except.UnPack(&t, 1);
            throw t;
        }

        case EXCEPTION_STRING: {
            char* t;
            int len;
            except.UnPack(&len, 1);
            if (len <= 0) {
                throw(char*)nullptr;
            }
            t = (char*)malloc(len * sizeof(char));
            except.UnPack(t, len);
            throw t;
        }

        case EXCEPTION_FLOAT: {
            float t;
            except.UnPack(&t, 1);
            throw t;
        }

        case EXCEPTION_DOUBLE: {
            double t;
            except.UnPack(&t, 1);
            throw t;
        }
        case EXCEPTION_POPC_STD: {
            pop_exception t(0);
            t.Serialize(except, false);
            throw t;
        }
        case EXCEPTION_OBJECT: {
            pop_interface t;
            t.Serialize(except, false);
            throw t;
        }
        default:
            pop_exception::pop_throw("Unknown exception in pop_buffer::CheckAndThrow");
    }
}
