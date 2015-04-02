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
    POPC_ComboxFactory instead of pop_combox_factory

  Note by LWK: The factory should generate the parent class pop_combox and not have 3 different methods for uds, mpi and socket
 */

#include <algorithm>

#include "popc_intface.h"

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#ifdef HAVE_LIBDL
#include <dlfcn.h>
#endif

#include "pop_combox_factory.h"
#include "pop_combox_socket.h"
#include "pop_combox_uds.h"
#include "pop_utils.h"

// Note by LWK: Added MPI_SUPPORT here to use 1 version of the file for both pseudodyn and dynamic
#ifdef MPI_SUPPORT
#include "pop_combox_mpi.h"
#endif

pop_combox_registration::pop_combox_registration(const char *name, int metrics, COMBOX_CREATOR creator) {
    pop_combox_factory *f=pop_combox_factory::GetInstance();
    f->Register(name,metrics, creator);
}

pop_combox * combox_socket_creator() {
    return new pop_combox_socket;
}

pop_combox* combox_uds_creator() {
    return new popc_combox_uds;
}

#ifdef MPI_SUPPORT
pop_combox * combox_mpi_creator() {
    return new popc_combox_mpi;
}
#endif

pop_combox_factory *pop_combox_factory::fact=nullptr;


pop_combox_factory::pop_combox_factory() {
    Register("socket", 0, combox_socket_creator);
    Register("uds", 0, combox_uds_creator);

#ifdef MPI_SUPPORT
    Register("mpi", 0, combox_mpi_creator);
#endif

    //Load combox from plugins....
    int metrics=100;
    COMBOX_CREATOR creator;
    std::string name;

    char *module=getenv("POPC_COMBOX_MODULES");
    if(module!=nullptr) {
        char *libs=popc_strdup(module);
        char *mod=strtok(libs,": ");
        while(mod!=nullptr) {
            void *h=LoadPlugin(mod, name, creator);

            if(h) {
                if(std::find(plugins.begin(), plugins.end(), h) == plugins.end()) {
                    plugins.push_back(h);
                    Register(name.c_str(),metrics,creator);
                }
            }
            mod=strtok(nullptr,": ");
        }
        free(libs);
    } else {
        const char* tmp = getenv("POPC_PLUGIN_LOCATION");
        std::string plugindir=tmp ? tmp : "";

#ifdef _PLUGINDIR
        if(plugindir==nullptr) {
            plugindir=_PLUGINDIR;
        }
#endif

        if(!plugindir.empty()) {
            std::string pluginmap(plugindir);
            pluginmap+="/pop_combox.map";
            FILE *map=fopen(pluginmap.c_str(),"r");
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
                            Register(name.c_str(),metrics,creator);
                        }
                    }
                }
                fclose(map);
            } else {
                LOG_DEBUG("unable to open plugin mapfile: %s", pluginmap.c_str()); // note: level set to debug
                DIR *dir=opendir(plugindir.c_str());
                if(dir!=nullptr) {
                    dirent *t;
                    while((t=readdir(dir))!=nullptr) {
                        if(!pop_utils::MatchWildcard(t->d_name,"*.so")) {
                            continue;
                        }
                        char fname[1024];
                        sprintf(fname,"%s/%s", plugindir.c_str(), t->d_name);
                        void *h=LoadPlugin(fname, name, creator);
                        if(h!=nullptr) {
                            if(std::find(plugins.begin(), plugins.end(), h) == plugins.end()) {
                                plugins.push_back(h);
                                Register(name.c_str(), metrics, creator);
                            }
                        }
                    }
                    closedir(dir);
                }
            }
        }
    }
}

pop_combox_factory::~pop_combox_factory() {
    for(auto& s : list){
        free(s.name);
    }
}

pop_combox_factory *pop_combox_factory::GetInstance() {
    if(fact==nullptr) {
        fact=new pop_combox_factory;
    }
    return fact;
}

pop_combox* pop_combox_factory::Create(const char * name) {
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

pop_combox* pop_combox_factory::Create(int index) {
    if(index<0 || static_cast<std::size_t>(index) >= list.size()) {
        return nullptr;
    }

    return list[index].creator();
}

void pop_combox_factory::GetNames(std::string &prots) {
    prots = std::accumulate(
        list.begin(), list.end(), std::string(),
        [](std::string& res, combox_factory_struct& t){ return res + " " + t.name; });
}

int pop_combox_factory::GetCount() {
    return list.size();
}

bool pop_combox_factory::Register(const char *name, int metrics, COMBOX_CREATOR creator) {
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

void * pop_combox_factory::LoadPlugin(char *fname,  std::string &name, COMBOX_CREATOR &f) {
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
