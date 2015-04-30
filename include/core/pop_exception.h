/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief POP-C++ exception. All runtime exceptions are thrown as pop_exception.
 *
 */

#ifndef POP_EXCEPTION_H
#define POP_EXCEPTION_H

#include <pop_base.h>
#include <exception>

// PAROC EXCEPTION CODE

#define USER_DEFINE_ERROR 10000
#define OBJECT_NO_RESOURCE USER_DEFINE_ERROR + 1
#define OBJECT_BIND_FAIL USER_DEFINE_ERROR + 2
#define OBJECT_MISMATCH_METHOD USER_DEFINE_ERROR + 3
#define CODE_SERVICE_FAIL USER_DEFINE_ERROR + 4

#define ALLOCATION_EXCEPTION USER_DEFINE_ERROR + 5
#define OBJECT_EXECUTABLE_NOTFOUND USER_DEFINE_ERROR + 6

#define POP_BUFFER_FORMAT USER_DEFINE_ERROR + 7

#define POP_APPSERVICE_FAIL USER_DEFINE_ERROR + 8
#define POP_JOBSERVICE_FAIL USER_DEFINE_ERROR + 9
#define POP_EXEC_FAIL USER_DEFINE_ERROR + 10

#define POP_BIND_BAD_REPLY USER_DEFINE_ERROR + 11

#define POP_NO_PROTOCOL USER_DEFINE_ERROR + 12
#define POP_NO_ENCODING USER_DEFINE_ERROR + 13

#define STD_EXCEPTION USER_DEFINE_ERROR + 14
#define ACK_NOT_RECEIVED USER_DEFINE_ERROR + 15
#define POP_NETWORK_FAIL USER_DEFINE_ERROR + 16

#define UNKNOWN_EXCEPTION USER_DEFINE_ERROR + 17
#define USER_DEFINE_LASTERROR USER_DEFINE_ERROR + 17

/**
 * @class pop_exception
 * @brief POP-C++ exception, used by POP-C++ runtime.
 *
 *  All runtime exceptions are thrown as pop_exception
 *
 * @author Tuan Anh Nguyen
 *
 *
 * Modifications
 * - Added AddInfo method and suppress create(...) method that was barely used + suppress SetExtra method (LW Jan 2015)
 */
class pop_exception : public pop_base, public std::exception {
public:
    pop_exception();
    pop_exception(int code);
    pop_exception(int code, const std::string& reason1, const std::string& reason2 = "");
    pop_exception(const std::string& reason1, const std::string& reason2 = "");
    ~pop_exception() throw() {
    }

    pop_exception& operator=(pop_exception& e);
    static void pop_throw(int code, const std::string& reason1 = "", const std::string& reason2 = "");
    static void pop_throw(const std::string& reason1, const std::string& reason2 = "");

    virtual void Serialize(pop_buffer& buf, bool pack);

    const std::string& Info() const;
    void AddInfo(const std::string& str);
    int Code() const;

    // Redefine the virtual what method of exception
    const char* what() const throw();

    // Old way: only prints an error message to stderr
    static void perror(const std::string& msg);

protected:
    static const char* paroc_errstr[17];
    std::string info;
    int errcode;
};

typedef pop_exception POPException;
#endif
