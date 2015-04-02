/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Buffer factory finder declaration
 *
 *
 */

#ifndef _POPC_BUFFER_FACTORY_FINDER_H
#define _POPC_BUFFER_FACTORY_FINDER_H

#include "pop_buffer_factory.h"
#include <string>

#define MAX_FACTORY 10

class pop_buffer_factory;

/**
 * @class pop_buffer_factory_finder
 * @brief Finds a buffer factory corresponding to the given buffer name, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class pop_buffer_factory_finder {
public:
    ~pop_buffer_factory_finder();

    int GetFactoryCount();
    pop_buffer_factory * GetFactory(int index);
    pop_buffer_factory * FindFactory(const std::string& name);
    static pop_buffer_factory_finder * GetInstance();
    bool GetBufferName(int index, std::string & bufferName);

private:
    pop_buffer_factory_finder();
    void *LoadPlugin(char *fname, pop_buffer_factory * &f);

    pop_buffer_factory * bfArray[MAX_FACTORY];
    int size;
    void *plugins[MAX_FACTORY];

    static pop_buffer_factory_finder* bff;

};
#endif
