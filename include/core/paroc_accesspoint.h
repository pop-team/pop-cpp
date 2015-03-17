/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief abstract network access point for parallel objects, used by POP-C++ runtime.
 *
 * UPDATES:
 * Authors      Date               Comment
 * clementval  2011/9/13   Add the method GetNoAddRef() and the variable _noaddref to be able to handle the THIS keyword correctly
 */

#ifndef POPC_ACCESSPOINT_H
#define POPC_ACCESSPOINT_H
#include "paroc_base.h"

class paroc_accesspoint: public paroc_base {
public:
    paroc_accesspoint();
    //  paroc_accesspoint(const char *hostport);
    paroc_accesspoint(const paroc_accesspoint &p);
    ~paroc_accesspoint();


    void SetAccessString(const std::string& hostport);
    const std::string& GetAccessString() const;
    bool IsEmpty() const;
    bool operator ==(const paroc_accesspoint &p) const;
    paroc_accesspoint & operator =(const paroc_accesspoint &p);
    bool IsSecure() const;
    void SetSecure();
    bool IsService() const;
    void SetAsService();
    void SetNoAddRef() ;
    bool GetNoAddRef() const;

    virtual void Serialize(paroc_buffer &buf, bool pack);
private:
    std::string endpoint;
    bool _service;
    bool _noaddref;
    int _security;
    enum security { NONSECURE, SECURE };
};

#endif
