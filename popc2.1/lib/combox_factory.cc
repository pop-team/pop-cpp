/**
 * File : combox_factory.cc
 * Author : Tuan Anh Nguyen
 * Description : Implementation of the communication box factory
 * Creation date : -
 * 
 * Modifications :
 * Authors		Date			Comment
 */


#include <string.h>
#include <sys/types.h>
#include <dirent.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_LIBDL
#include <dlfcn.h>
#endif

#include "paroc_combox_factory.h"
#include "paroc_combox_socket.h"

paroc_combox_registration::paroc_combox_registration(const char *name, int metrics, COMBOX_CREATOR creator)
{
	paroc_combox_factory *f=paroc_combox_factory::GetInstance();
	f->Register(name,metrics, creator);
}

paroc_combox * combox_socket_creator()
{
	return new paroc_combox_socket;
}

paroc_combox_factory *paroc_combox_factory::fact=NULL;


paroc_combox_factory::paroc_combox_factory()
{
	
	Register("socket",0,combox_socket_creator);

	//Load combox from plugins....
	int metrics=100;
	COMBOX_CREATOR creator;
	POPString name;

	char *module=getenv("POPC_COMBOX_MODULES");
	if (module!=NULL)
	{
		char *libs=strdup(module);
		char *mod=strtok(libs,": ");
		while (mod!=NULL)
		{
			void *h=LoadPlugin(mod, name, creator);

			if (h!=NULL)
			{
				int n=plugins.GetSize();
				bool loaded=false;
				for (int i=0;i<n;i++)
					if (plugins[i]==h)
					{
						loaded=true;
						break;
					}

				if (!loaded)
				{
					plugins.InsertAt(-1,h);
					Register(name,metrics,creator);
				}
			}
			mod=strtok(NULL,": ");
		}
		free(libs);
	}
	else
	{
		POPString plugindir;
		plugindir=getenv("POPC_PLUGIN_LOCATION");
#ifdef _PLUGINDIR
		if (plugindir==NULL) plugindir=_PLUGINDIR;
#endif

		if (plugindir!=NULL)
		{
			POPString pluginmap(plugindir);
			pluginmap+="/paroc_combox.map";
			FILE *map=fopen(pluginmap,"r");
			if (map!=NULL)
			{
				char line[1024];
				char fname[1024];
				while (fgets(line,1023,map)!=NULL)
				{
					int t=sscanf(line, "%s %d",fname,&metrics);
					if (t<1) continue;
					if (t==1) metrics=100;
					if (*fname=='#') continue;

					void *h=LoadPlugin(fname, name, creator);
					if (h!=NULL)
					{
						bool loaded=false;
						int n=plugins.GetSize();
						for (int j=0;j<n;j++) if (h==plugins[j])
							{
								loaded=true;
								break;
							}

						if (!loaded)
						{
							plugins.InsertAt(-1,h);
							Register(name,metrics,creator);
						}
					}
				}
				fclose(map);
			}
			else
			{
				DEBUG("WARNING: unable to open plugin mapfile: %s",(const char *)pluginmap);
				DIR *dir=opendir(plugindir);
				if (dir!=NULL)
				{
					dirent *t;
					while ((t=readdir(dir))!=NULL)
					{
						if (!paroc_utils::MatchWildcard(t->d_name,"*.so")) continue;
						char fname[1024];
						sprintf(fname,"%s/%s", (const char *)plugindir, t->d_name);
						void *h=LoadPlugin(fname, name, creator);
						if (h!=NULL)
						{
							bool loaded=false;
							int n=plugins.GetSize();
							for (int j=0;j<n;j++) if (h==plugins[j])
								{
									loaded=true;
									break;
								}

							if (!loaded)
							{
								plugins.InsertAt(-1,h);
								Register(name,metrics,creator);
							}
						}
					}
					closedir(dir);
				}
			}
		}
	}
}

paroc_combox_factory::~paroc_combox_factory()
{
	POSITION pos=list.GetHeadPosition();
	while (pos!=NULL)
	{
		combox_factory_struct &t=list.GetNext(pos);
		free(t.name);
	}
}

paroc_combox_factory *paroc_combox_factory::GetInstance()
{
	if (fact==NULL) fact=new paroc_combox_factory;
	return fact;
}

void paroc_combox_factory::Destroy()
{
	if (fact!=NULL) delete fact;
	fact=NULL;
}

paroc_combox* paroc_combox_factory::Create(const char * name)
{
	DEBUG("Create a combox : %s\n", name);
	if (name==NULL) return NULL;
	POSITION pos=list.GetHeadPosition();
	while (pos!=NULL)
	{
		combox_factory_struct &t=list.GetNext(pos);
		if (strcmp(name,t.name)==0) return t.creator();
	}
	return NULL;
}

paroc_combox* paroc_combox_factory::Create(int index)
{
	if (index<0 || index>=GetCount()) return NULL;
	POSITION pos=list.GetHeadPosition();
	while (pos!=NULL)
	{
		combox_factory_struct &t=list.GetNext(pos);
		if (index==0) return t.creator();
		index--;
	}
	return NULL;
}

void paroc_combox_factory::GetNames(POPString &prots)
{
	prots="";
	POSITION pos=list.GetHeadPosition();
	while (pos!=NULL)
	{
		combox_factory_struct &t=list.GetNext(pos);
		DEBUG("%s\n", t.name);
		prots+=t.name;
		if (pos!=NULL) prots+=" ";
	}
}

int paroc_combox_factory::GetCount()
{
	return list.GetCount();
}

bool paroc_combox_factory::Register(const char *name, int metrics, COMBOX_CREATOR creator)
{
	DEBUG("[Combox] Register %s\n", name);
	if (name==NULL || creator==NULL) return false;
	combox_factory_struct t;

	POSITION pos=list.GetHeadPosition();
	POSITION insertpos=NULL;

	while (pos!=NULL)
	{
		POSITION old=pos;
		combox_factory_struct &t=list.GetNext(pos);
		if (strcmp(t.name, name)==0) return false;

		if (metrics<t.metrics && insertpos==NULL)
		{
			insertpos=old;
		}
	}
	if (insertpos==NULL)
	{
		combox_factory_struct &el=list.AddTailNew();
		el.name=strdup(name);
		el.metrics=metrics;
		el.creator=creator;
	}
	else
	{
		combox_factory_struct el;
		el.name=strdup(name);
		el.metrics=metrics;
		el.creator=creator;
		list.InsertBefore(insertpos, el);
	}
	return true;
}

void * paroc_combox_factory::LoadPlugin(char *fname,  POPString &name, COMBOX_CREATOR &f)
{
#ifdef HAVE_LIBDL
	void *handle=dlopen(fname,RTLD_LAZY| RTLD_LOCAL);
	if (handle==NULL)
	{
		DEBUG("ERROR:%s: %s",fname,dlerror());
		return NULL;
	}
//  DEBUG("Module loaded: %s",fname);

	LOAD_PROTOCOL func;
	func=(LOAD_PROTOCOL)dlsym(handle,"LoadProtocol");
	if (func==NULL || func(name,f)!=0)
	{
		DEBUG("Fail to create the combox from %s", fname);
		dlclose(handle);
		return NULL;
	}
	return handle;
#else
	return NULL;
#endif
}
