/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of buffer factory finder.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_BufferFactoryFinder instead of paroc_buffer_factory_finder
 */

#include "popc_intface.h"

#include "paroc_buffer_factory_finder.h"
#include "paroc_buffer_xdr_factory.h"
#include "paroc_buffer_raw_factory.h"
#include "paroc_utils.h"
#include "config.h"

#ifdef HAVE_LIBDL
#include <dlfcn.h>
#endif

paroc_buffer_factory_finder *paroc_buffer_factory_finder::bff=NULL;

paroc_buffer_factory_finder::paroc_buffer_factory_finder() {

    //Initialize the static array
    int metrics[MAX_FACTORY];

    /*bfArray[0] = new paroc_buffer_raw_factory();
    bfArray[1] = new paroc_buffer_xdr_factory();
    metrics[0] = metrics[1]=0;
    plugins[0] = plugins[1] = NULL;
    size = 2;*/


    bfArray[0] = new paroc_buffer_xdr_factory();
//  bfArray[0] = new paroc_buffer_raw_factory();
    metrics[0] = 0;
    plugins[0] = NULL;
    size = 1;

    char *module = getenv("POPC_LOADABLE_MODULES");
    if(module != NULL) {
        char *libs = popc_strdup(module);
        char *mod = strtok(module,":");
        while(mod != NULL && size < MAX_FACTORY) {
            metrics[size] = 1;
#ifdef HAVE_LIBDL
            plugins[size] = LoadPlugin(mod, bfArray[size]);
            if(plugins[size] != NULL) {
                bool loaded = false;
                for(int j = 0; j < size; j++) {
                    if(plugins[size] == plugins[j]) {
                        loaded = true;
                        popc_dlclose(plugins[size]);
                        break;
                    }
                }
                if(!loaded) {
                    size++;
                }
            }
#endif
            mod = strtok(NULL, ":");
        }
        free(libs);
    }

    POPString plugindir;
    plugindir = getenv("POPC_PLUGIN_LOCATION");
#ifdef _PLUGINDIR
    if(plugindir == NULL) {
        plugindir = _PLUGINDIR;
    }
#endif


    if(plugindir.c_str() != NULL) {
        POPString pluginmap(plugindir);
        pluginmap += "/paroc_buffer.map";
        FILE *map = fopen(pluginmap.c_str(), "r");
        if(map != NULL) {
            char line[1024];
            char fname[1024];
            int metric;
            while(fgets(line,1023,map) != NULL && size < MAX_FACTORY) {
                int t = sscanf(line, "%s %d", fname, &metric);
                if(t<1) {
                    continue;
                }
                if(*fname == '#') {
                    continue;
                }
                if(t == 1) {
                    metric = 1;
                }
                metrics[size] = metric;
#ifdef HAVE_LIBDL
                plugins[size] = LoadPlugin(fname, bfArray[size]);
                if(plugins[size] != NULL) {
                    bool loaded = false;
                    for(int j = 0; j < size; j++) {
                        if(plugins[size] == plugins[j]) {
                            loaded = true;
                            popc_dlclose(plugins[size]);
                            break;
                        }
                    }
                    if(!loaded) {
                        size++;
                    }
                }
#endif
            }
            fclose(map);
        } else {
            DIR *dir = opendir(plugindir.c_str());
            if(dir != NULL) {
                dirent *t;
                while((t = readdir(dir))!=NULL && size<MAX_FACTORY) {
                    if(!paroc_utils::MatchWildcard(t->d_name,"*.so")) {
                        continue;
                    }
                    char fname[1024];
                    sprintf(fname,"%s/%s", plugindir.c_str(), t->d_name);
                    metrics[size]=1;
#ifdef HAVE_LIBDL
                    plugins[size]=LoadPlugin(fname, bfArray[size]);
                    if(plugins[size]!=NULL) {
                        bool loaded=false;
                        for(int j=0; j<size; j++) if(plugins[size]==plugins[j]) {
                                loaded=true;
                                popc_dlclose(plugins[size]);
                                break;
                            }

                        if(!loaded) {
                            size++;
                        }
                    }
#endif
                }
                closedir(dir);
            }
        }
    }

    //Now sorting...
    for(int i=0; i<size; i++) {
        for(int j=size-1; j>i; j--) {
            if(metrics[j]<metrics[j-1]) {
                int t=metrics[j];
                metrics[j]=metrics[j-1];
                metrics[j-1]=t;
                paroc_buffer_factory *f=bfArray[j];
                bfArray[j]=bfArray[j-1];
                bfArray[j-1]=f;
            }
        }
    }
}

paroc_buffer_factory_finder::~paroc_buffer_factory_finder() {
    bff=NULL;
    for(int i=0; i<size; i++) {
        bfArray[i]->Destroy();
    }

#ifdef HAVE_LIBDL
    for(int i=0; i<size; i++) {
        if(plugins[i]!=NULL) {
            popc_dlclose(plugins[i]);
        }
    }
#endif
}


void * paroc_buffer_factory_finder::LoadPlugin(char *fname, paroc_buffer_factory * &f) {
#ifdef HAVE_LIBDL
    void *handle=popc_dlopen(fname,RTLD_LAZY| RTLD_LOCAL);
    if(!handle) {
        return NULL;
    }

    paroc_buffer_factory * (*creator)();
    creator = (paroc_buffer_factory * (*)())popc_dlsym(handle,"ParocBufferFactory");
    if(creator != NULL) {
        f = creator();
        if(!f) {
            popc_dlclose(handle);
            return NULL;
        }
    } else {
        LOG_ERROR("POP-C++ Error: [CORE]:%s: %s",fname,popc_dlerror());
        popc_dlclose(handle);
        return NULL;
    }

    return handle;
#else
    ((void)fname);  //Silence warning
    ((void)f);      //Silence warning
    return NULL;
#endif
}



paroc_buffer_factory_finder* paroc_buffer_factory_finder::GetInstance() {
    if(bff==NULL) {
        bff=new paroc_buffer_factory_finder();
        return paroc_buffer_factory_finder::bff;
    } else {
        return paroc_buffer_factory_finder::bff;
    }
}

int paroc_buffer_factory_finder::GetFactoryCount() {
    return size;
}

paroc_buffer_factory* paroc_buffer_factory_finder::GetFactory(int index) {
    return bfArray[index];
}

bool paroc_buffer_factory_finder::GetBufferName(int index, POPString & bufferName) {

    if(index < 0 || index >= size) {
        return false;
    }
    bfArray[index]->GetBufferName(bufferName);
    return true;

}


paroc_buffer_factory* paroc_buffer_factory_finder::FindFactory(const POPString bufferName) {
    int i;
    POPString s;

    for(i=0; i < size; i++) {
        bfArray[i]->GetBufferName(s);
        if(paroc_utils::isEqual(s.c_str(), bufferName.c_str())) {
            return bfArray[i];
        }
    }
    return NULL;


}

/*
POPString * paroc_factory_finder::GetFactoryList(){
  return new POPString("socket");
}
*/
