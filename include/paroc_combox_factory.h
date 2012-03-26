/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: factory that creates a proper combox from the given name
 */

#ifndef POPC_COMBOX_FACTORY_H
#define POPC_COMBOX_FACTORY_H

#include <paroc_combox.h>
#include <paroc_list.h>
#include <paroc_string.h>


/*This abstract class declares an interface creating abstract combox*/

typedef paroc_combox* (*COMBOX_CREATOR)();
typedef int (*LOAD_PROTOCOL)(paroc_string &, COMBOX_CREATOR &);

struct combox_factory_struct
{
	char *name;
	int metrics;

	COMBOX_CREATOR creator;
};


/**
 * @class paroc_combox_factory
 * @brief Factory that creates a proper combox from the given name, used by POP-C++ runtime.
 * @author Tuan Anh Nguyen
 *
 */
class paroc_combox_factory
{
protected:
	paroc_combox_factory();
	~paroc_combox_factory();

public:
	static paroc_combox_factory *GetInstance();
	void Destroy();

	paroc_combox* Create(const char * name);
	paroc_combox* Create(int index);

	void GetNames(paroc_string &prots);
	int GetCount();

	bool Register(const char *name, int metrics, COMBOX_CREATOR creator);

	void *LoadPlugin(char *fname,  paroc_string &name, COMBOX_CREATOR &f);

private:
	static paroc_combox_factory *fact;

private:
	paroc_list<combox_factory_struct> list;
	paroc_array<void *> plugins;

};

class paroc_combox_registration
{
public:
	paroc_combox_registration(const char *name, int metrics, COMBOX_CREATOR creator);
};

#define COMBOX(x) extern paroc_combox_registration x;

#endif // POPC_PROTOCOL_FACTORY_H
