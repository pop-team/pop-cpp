/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief abstract network access point for parallel objects, used by POP-C++ runtime.
 *
 * UPDATES:
 * Authors      Date               Comment
 * clementval  2011/9/13   Add the method GetNoAddRef() and the variable _noaddref to be able to handle the THIS keyword
 *correctly
 */

#ifndef POP_ACCESSPOINT_H
#define POP_ACCESSPOINT_H
#include "pop_base.h"

class pop_accesspoint : public pop_base {
public:
    pop_accesspoint();
    //  pop_accesspoint(const char *hostport);
    pop_accesspoint(const pop_accesspoint& p);
    ~pop_accesspoint();

    void SetAccessString(const std::string& hostport);
    const std::string& GetAccessString() const;
    bool IsEmpty() const;
    bool operator==(const pop_accesspoint& p) const;
    pop_accesspoint& operator=(const pop_accesspoint& p);
    bool IsSecure() const;
    void SetSecure();
    bool IsService() const;
    void SetAsService();
    void SetNoAddRef();
    bool GetNoAddRef() const;

    virtual void Serialize(pop_buffer& buf, bool pack);

private:
    std::string endpoint;
    bool _service;
    bool _noaddref;
    int _security;
    enum security { NONSECURE, SECURE };
};

#endif
