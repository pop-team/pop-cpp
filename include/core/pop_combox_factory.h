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

#ifndef POP_COMBOX_FACTORY_H
#define POP_COMBOX_FACTORY_H

#include <vector>

#include "pop_combox.h"

/*This abstract class declares an interface creating abstract combox*/

typedef pop_combox* (*COMBOX_CREATOR)();
typedef int (*LOAD_PROTOCOL)(std::string &, COMBOX_CREATOR &);

struct combox_factory_struct {
    char *name;
    int metrics;

    COMBOX_CREATOR creator;

    combox_factory_struct(){}
    combox_factory_struct(char* name, int metrics, COMBOX_CREATOR creator) : name(name), metrics(metrics), creator(creator) {}
};

/**
 * @class pop_combox_factory
 * @brief Factory that creates a proper combox from the given name, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class pop_combox_factory {
protected:
    pop_combox_factory();

public:
    ~pop_combox_factory();

    //Singleton functions
    static pop_combox_factory& get_instance();
    static void release_instance();

    pop_combox* Create(const char * name);
    pop_combox* Create(int index);

    void GetNames(std::string &prots);
    int GetCount();

    bool Register(const char *name, int metrics, COMBOX_CREATOR creator);

    void *LoadPlugin(char *fname,  std::string &name, COMBOX_CREATOR &f);

private:
    static pop_combox_factory* fact;

private:
    std::vector<combox_factory_struct> list;
    std::vector<void *> plugins;
};

class pop_combox_registration {
public:
    pop_combox_registration(const char *name, int metrics, COMBOX_CREATOR creator);
};

#define COMBOX(x) extern pop_combox_registration x;

#endif // POPC_PROTOCOL_FACTORY_H
