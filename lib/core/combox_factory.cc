/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief Implementation of the communication box factory.
 *
 *
 */

/*
  Deeply need refactoring:
    POPC_ComboxFactory instead of paroc_combox_factory

  Note by LWK: The factory should generate the parent class paroc_combox and not have 3 different methods for uds, mpi and socket
 */

#include <algorithm>

#include "popc_intface.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_LIBDL
#include <dlfcn.h>
#endif

#include "paroc_combox_factory.h"
#include "paroc_combox_socket.h"
//#include "popc_combox_uds.h"
#include "paroc_utils.h"
#ifdef MPI_SUPPORT
// Note by LWK: Added MPI_SUPPORT here to use 1 version of the file for both pseudodyn and dynamic
#include "popc_combox_mpi.h"
#endif

paroc_combox_registration::paroc_combox_registration(const char *name, int metrics, COMBOX_CREATOR creator) {
    paroc_combox_factory *f=paroc_combox_factory::GetInstance();
    f->Register(name,metrics, creator);
}

paroc_combox * combox_socket_creator() {
    return new paroc_combox_socket;
}

paroc_combox* combox_uds_creator() {
 //   return new popc_combox_uds; // TODO LW: This should be uncommented !
    return nullptr;
}

#ifdef MPI_SUPPORT
paroc_combox * combox_mpi_creator() {
    return new popc_combox_mpi;
}
#endif

paroc_combox_factory *paroc_combox_factory::fact=nullptr;


paroc_combox_factory::paroc_combox_factory() {
//Note(BW): UDS initialization by the broker fails, therefore, disabled for now
//    Register("uds", 0, combox_uds_creator);
    Register("socket", 0, combox_socket_creator);
#ifdef MPI_SUPPORT
    Register("mpi", 0, combox_mpi_creator);
#endif

    //Load combox from plugins....
    int metrics=100;
    COMBOX_CREATOR creator;
    POPString name;

    char *module=getenv("POPC_COMBOX_MODULES");
    if(module!=nullptr) {
        char *libs=popc_strdup(module);
        char *mod=strtok(libs,": ");
        while(mod!=nullptr) {
            void *h=LoadPlugin(mod, name, creator);

            if(h) {
                if(std::find(plugins.begin(), plugins.end(), h) == plugins.end()) {
                    plugins.push_back(h);
                    Register(name,metrics,creator);
                }
            }
            mod=strtok(nullptr,": ");
        }
        free(libs);
    } else {
        POPString plugindir;
        plugindir=getenv("POPC_PLUGIN_LOCATION");
#ifdef _PLUGINDIR
        if(plugindir==nullptr) {
            plugindir=_PLUGINDIR;
        }
#endif

        if(plugindir!=nullptr) {
            POPString pluginmap(plugindir);
            pluginmap+="/paroc_combox.map";
            FILE *map=fopen(pluginmap,"r");
            if(map!=nullptr) {
                char line[1024];
                char fname[1024];
                while(fgets(line,1023,map)!=nullptr) {
                    int t=sscanf(line, "%s %d",fname,&metrics);
                    if(t<1) {
                        continue;
                    }
                    if(t==1) {
                        metrics=100;
                    }
                    if(*fname=='#') {
                        continue;
                    }

                    void *h=LoadPlugin(fname, name, creator);
                    if(h!=nullptr) {
                        if(std::find(plugins.begin(), plugins.end(), h) == plugins.end()) {
                            plugins.push_back(h);
                            Register(name,metrics,creator);
                        }
                    }
                }
                fclose(map);
            } else {
                LOG_DEBUG("unable to open plugin mapfile: %s",(const char *)pluginmap); // note: level set to debug
                DIR *dir=opendir(plugindir);
                if(dir!=nullptr) {
                    dirent *t;
                    while((t=readdir(dir))!=nullptr) {
                        if(!paroc_utils::MatchWildcard(t->d_name,"*.so")) {
                            continue;
                        }
                        char fname[1024];
                        sprintf(fname,"%s/%s", (const char *)plugindir, t->d_name);
                        void *h=LoadPlugin(fname, name, creator);
                        if(h!=nullptr) {
                            if(std::find(plugins.begin(), plugins.end(), h) == plugins.end()) {
                                plugins.push_back(h);
                                Register(name, metrics, creator);
                            }
                        }
                    }
                    closedir(dir);
                }
            }
        }
    }
}

paroc_combox_factory::~paroc_combox_factory() {
    for(auto& s : list){
        free(s.name);
    }
}

paroc_combox_factory *paroc_combox_factory::GetInstance() {
    if(fact==nullptr) {
        fact=new paroc_combox_factory;
    }
    return fact;
}

void paroc_combox_factory::Destroy() {
    if(fact!=nullptr) {
        delete fact;
    }
    fact=nullptr;
}

paroc_combox* paroc_combox_factory::Create(const char * name) {
    LOG_DEBUG("Create a combox : %s", name);
    if(name == nullptr) {
        return nullptr;
    }
    for(auto& t : list){
        if(strcmp(name, t.name) == 0) {
            return t.creator();
        }
    }
    return nullptr;
}

paroc_combox* paroc_combox_factory::Create(int index) {
    if(index<0 || static_cast<std::size_t>(index) >= list.size()) {
        return nullptr;
    }

    return list[index].creator();
}

void paroc_combox_factory::GetNames(POPString &prots) {
    prots = std::accumulate(
        list.begin(), list.end(), POPString(),
        [](POPString& res, combox_factory_struct& t){ return res + " " + t.name; });
}

int paroc_combox_factory::GetCount() {
    return list.size();
}

bool paroc_combox_factory::Register(const char *name, int metrics, COMBOX_CREATOR creator) {
    LOG_DEBUG("[Combox] Register %s", name);

    if(!name || !creator) {
        return false;
    }

    //If the name is already present, return false

    for(auto& t : list){
        if(strcmp(t.name, name) == 0) {
            return false;
        }
    }

    //Otherwise find the correct position inside the list and insert it

    auto it = std::find_if(list.begin(), list.end(),
        [metrics](combox_factory_struct& t){ return metrics < t.metrics; });

    if(it == list.end()){
        list.emplace_back(popc_strdup(name), metrics, creator);
    } else {
        list.emplace(it, popc_strdup(name), metrics, creator);
    }

    return true;
}

void * paroc_combox_factory::LoadPlugin(char *fname,  POPString &name, COMBOX_CREATOR &f) {
#ifdef HAVE_LIBDL
    LOG_INFO("Load plugin %s", fname);
    void *handle = popc_dlopen(fname, RTLD_LAZY| RTLD_LOCAL);
    if(handle == nullptr) {
        LOG_ERROR("%s: %s",fname,dlerror());
        return nullptr;
    }

    LOAD_PROTOCOL func;
    func = (LOAD_PROTOCOL)popc_dlsym(handle, "LoadProtocol");
    if(func == nullptr || func(name, f) != 0) {
        popc_dlclose(handle);
        return nullptr;
    }
    return handle;
#else
	(void) fname;
	(void) name;
	(void) f;
    return nullptr;
#endif
}
