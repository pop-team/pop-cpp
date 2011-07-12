/*
AUTHORS: Tuan Anh Nguyen

DESCRIPTION: implementation of buffer factory finder
 */

#include <stdio.h>

#include "paroc_buffer_factory_finder.h"
#include "paroc_buffer_xdr_factory.h"
#include "paroc_buffer_raw_factory.h"

#include <sys/types.h>
#include <dirent.h>

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_LIBDL
#include <dlfcn.h>
#endif

paroc_buffer_factory_finder *paroc_buffer_factory_finder::bff=NULL;

paroc_buffer_factory_finder::paroc_buffer_factory_finder()
{

	//Initialize the static array
	int metrics[MAX_FACTORY];

	bfArray[0]=new paroc_buffer_raw_factory();
	bfArray[1]=new paroc_buffer_xdr_factory();
	metrics[0]=metrics[1]=0;
	plugins[0]=plugins[1]=NULL;
	size=2;

	char *module=getenv("POPC_LOADABLE_MODULES");
	if (module!=NULL)
	{
		char *libs=strdup(module);
		char *mod=strtok(module,":");
		while (mod!=NULL && size<MAX_FACTORY)
		{
			metrics[size]=1;
			plugins[size]=LoadPlugin(mod,bfArray[size]);
			if (plugins[size]!=NULL)
			{
				bool loaded=false;
				for (int j=0;j<size;j++) if (plugins[size]==plugins[j])
					{
						DEBUG("%s already loaded");
						loaded=true;
						dlclose(plugins[size]);
						break;
					}

				if (!loaded) size++;
			}
			mod=strtok(NULL,":");
		}
		free(libs);
	}

	paroc_string plugindir;
	plugindir=getenv("POPC_PLUGIN_LOCATION");
#ifdef _PLUGINDIR
	if (plugindir==NULL) plugindir=_PLUGINDIR;
#endif


	if (plugindir!=NULL)
	{
		paroc_string pluginmap(plugindir);
		pluginmap+="/paroc_buffer.map";
		FILE *map=fopen(pluginmap,"r");
		if (map!=NULL)
		{
			char line[1024];
			char fname[1024];
			int metric;
			while (fgets(line,1023,map)!=NULL && size<MAX_FACTORY)
			{
				int t=sscanf(line, "%s %d",fname,&metric);
				if (t<1) continue;
				if (*fname=='#') continue;
				if (t==1) metric=1;
				metrics[size]=metric;
				plugins[size]=LoadPlugin(fname, bfArray[size]);
				if (plugins[size]!=NULL)
				{
					bool loaded=false;
					for (int j=0;j<size;j++) if (plugins[size]==plugins[j])
						{
							loaded=true;
							dlclose(plugins[size]);
							break;
						}

					if (!loaded) size++;
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
				while ((t=readdir(dir))!=NULL && size<MAX_FACTORY)
				{
					if (!paroc_utils::MatchWildcard(t->d_name,"*.so")) continue;
					char fname[1024];
					sprintf(fname,"%s/%s", (const char *)plugindir, t->d_name);
					metrics[size]=1;
					plugins[size]=LoadPlugin(fname, bfArray[size]);
					if (plugins[size]!=NULL)
					{
						bool loaded=false;
						for (int j=0;j<size;j++) if (plugins[size]==plugins[j])
							{
								loaded=true;
								dlclose(plugins[size]);
								break;
							}

						if (!loaded) size++;
					}
				}
				closedir(dir);
			}
		}
	}

	//Now sorting...
	for (int i=0;i<size;i++)
		for (int j=size-1;j>i;j--) if (metrics[j]<metrics[j-1])
			{
				int t=metrics[j];
				metrics[j]=metrics[j-1];
				metrics[j-1]=t;
				paroc_buffer_factory *f=bfArray[j];
				bfArray[j]=bfArray[j-1];
				bfArray[j-1]=f;
			}

}

paroc_buffer_factory_finder::~paroc_buffer_factory_finder()
{
	bff=NULL;
	for (int i=0;i<size;i++) bfArray[i]->Destroy();

#ifdef HAVE_LIBDL
	for (int i=0;i<size;i++) if (plugins[i]!=NULL) dlclose(plugins[i]);
#endif
}


void * paroc_buffer_factory_finder::LoadPlugin(char *fname, paroc_buffer_factory * &f)
{
#ifdef HAVE_LIBDL
	void *handle=dlopen(fname,RTLD_LAZY| RTLD_LOCAL);
	if (handle==NULL) return NULL;
	//  DEBUG("Module loaded: %s",fname);

	paroc_buffer_factory * (*creator)();
	creator=(paroc_buffer_factory * (*)())dlsym(handle,"ParocBufferFactory");
	if (creator!=NULL)
	{
		f=creator();
		if (f==NULL)
		{
			DEBUG("Fail to create the buffer factory from %s", fname);
			dlclose(handle);
			return NULL;
		}
	}
	else
	{
		DEBUG("ERROR:%s: %s",fname,dlerror());
		dlclose(handle);
		return NULL;
	}
	return handle;
#else
	return NULL;
#endif
}



paroc_buffer_factory_finder* paroc_buffer_factory_finder::GetInstance() {

	if (bff==NULL) {
		bff=new paroc_buffer_factory_finder();
		return paroc_buffer_factory_finder::bff;
	}
	else {
		return paroc_buffer_factory_finder::bff;
	}
}

int paroc_buffer_factory_finder::GetFactoryCount() {
	return size;
}

paroc_buffer_factory* paroc_buffer_factory_finder::GetFactory(int index) {
	return bfArray[index];
}

bool paroc_buffer_factory_finder::GetBufferName(int index, paroc_string & bufferName) {

	if (index < 0 || index >= size) return false;
	bfArray[index]->GetBufferName(bufferName);
	return true;

}


paroc_buffer_factory* paroc_buffer_factory_finder::FindFactory(const paroc_string bufferName) {

	int i;
	paroc_string s;

	for (i=0; i < size; i++) {
		bfArray[i]->GetBufferName(s);
		if (paroc_utils::isEqual(s, bufferName)) return bfArray[i];
	}
	return NULL;


}

/*
paroc_string * paroc_factory_finder::GetFactoryList(){
  return new paroc_string("socket");
}
*/
