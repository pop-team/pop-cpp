/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief factory that creates a proper combox from the given name
 *
 */

#ifndef POPC_COMBOX_FACTORY_H
#define POPC_COMBOX_FACTORY_H

#include <vector>

#include "paroc_combox.h"

/*This abstract class declares an interface creating abstract combox*/

typedef paroc_combox* (*COMBOX_CREATOR)();
typedef int (*LOAD_PROTOCOL)(std::string &, COMBOX_CREATOR &);

struct combox_factory_struct {
    char *name;
    int metrics;

    COMBOX_CREATOR creator;

    combox_factory_struct(){}
    combox_factory_struct(char* name, int metrics, COMBOX_CREATOR creator) : name(name), metrics(metrics), creator(creator) {}
};

/**
 * @class paroc_combox_factory
 * @brief Factory that creates a proper combox from the given name, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class paroc_combox_factory {
protected:
    paroc_combox_factory();
    ~paroc_combox_factory();

public:
    static paroc_combox_factory *GetInstance();
    void Destroy(); // TODO LW: this method only deletes fact. Check with BW!

    paroc_combox* Create(const char * name);
    paroc_combox* Create(int index);

    void GetNames(std::string &prots);
    int GetCount();

    bool Register(const char *name, int metrics, COMBOX_CREATOR creator);

    void *LoadPlugin(char *fname,  std::string &name, COMBOX_CREATOR &f);

private:
    static paroc_combox_factory *fact;

private:
    std::vector<combox_factory_struct> list;
    std::vector<void *> plugins;

};

class paroc_combox_registration {
public:
    paroc_combox_registration(const char *name, int metrics, COMBOX_CREATOR creator);
};

#define COMBOX(x) extern paroc_combox_registration x;

#endif // POPC_PROTOCOL_FACTORY_H
