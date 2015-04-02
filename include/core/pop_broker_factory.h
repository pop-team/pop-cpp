/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief broker factory declaration for instantiate brokers
 *
 *
 */

#ifndef _POPC_BROKER_FACTORY_H_
#define  _POPC_BROKER_FACTORY_H_

#include <vector>
#include <pop_broker.h>

typedef pop_broker *(*initbrokerfunc)();
typedef bool (*ispackedfunc)(const char *objname);

struct pop_broker_init {
    initbrokerfunc func;
    std::string objname;
};

/**
 * @class pop_broker_factory
 * @brief Broker factory declaration for instantiate brokers, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class pop_broker_factory {
public:
    /**
     * @brief Constructor, adds this pop_broker_factory to the global list
     * @param func Initialization function pointer
     * @param name Object name
     */
    pop_broker_factory(initbrokerfunc func, const char *name);

    /**
     * @brief Create a broker for the given object
     * @param objname Object name
     */
    static pop_broker *Create(const char *objname);

    /**
     * @brief Returns the list of brokers
     * @param objlist Output
     */
    static void List(std::vector<std::string>& objlist);

    /**
     * @brief Create a broker
     *
     * Used at the beginning of object main. Parses the arguments.
     *
     * @param argc
     * @param argv
     * @return broker
     */
    static pop_broker *Create(int *argc, char ***argv);

    /**
     * @brief Print brokers
     * @param abspath
     * @param longformat Print full format or name only
     */
    static void PrintBrokers(const char *abspath, bool longformat);
    // static void PrintBrokersMPI(const char *abspath);

    /**
     * @brief Returns true if an object is not on brokerlist
     * @param objname Name
     */
    bool test(const char *objname);

    static ispackedfunc CheckIfPacked; // Since this method is created by the parser, we have to declare a fct pointer for it

private:
    static std::vector<pop_broker_init> *brokerlist;
};

#endif
