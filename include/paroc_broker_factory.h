/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: broker factory declaration for instantiate brokers
 */

#ifndef _POPC_BROKER_FACTORY_H_
#define  _POPC_BROKER_FACTORY_H_

#include <paroc_broker.h>
#include <paroc_list.h>

typedef paroc_broker *(*initbrokerfunc)();
typedef bool (*ispackedfunc)(const char *objname);

struct paroc_broker_init
{
	initbrokerfunc func;
	paroc_string objname;
};

typedef paroc_list<paroc_broker_init> paroc_list_broker;
typedef paroc_list<paroc_string> paroc_list_string;

/**
 * @class paroc_broker_factory
 * @brief Broker factory declaration for instantiate brokers, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 */
class paroc_broker_factory
{
public:
	/**
	 * @brief Constructor, adds this paroc_broker_factory to the global list
	 * @param func Initialization function pointer
	 * @param name Object name
	 */
	paroc_broker_factory(initbrokerfunc func, const char *name);

	/**
	 * @brief Create a broker for the given object
	 * @param objname Object name
	 */
	static paroc_broker *Create(const char *objname);

	/**
	 * @brief Returns the list of brokers
	 * @param objlist Output
	 */
	static void List(paroc_list_string &objlist);

	/**
	 * @brief Create a broker
	 *
	 * Used at the beginning of object main. Parses the arguments.
	 *
	 * @param argc
	 * @param argv
	 * @return broker
	 */
	static paroc_broker *Create(int *argc, char ***argv);

	/**
	 * @brief Print brokers
	 * @param abspath
	 * @param longformat Print full format or name only
	 */
	static void PrintBrokers(const char *abspath, bool longformat);

	/**
	 * @brief Returns true if an object is not on brokerlist
	 * @param objname Name
	 */
	bool Test(const char *objname);

	static ispackedfunc CheckIfPacked; // Since this method is created by the parser, we have to declare a fct pointer for it

private:
	static paroc_list_broker *brokerlist;
};

#endif
