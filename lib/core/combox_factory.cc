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
    return NULL;
}

#ifdef MPI_SUPPORT
paroc_combox * combox_mpi_creator() {
    return new popc_combox_mpi;
}
#endif

paroc_combox_factory *paroc_combox_factory::fact=NULL;


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
    if(module!=NULL) {
        char *libs=popc_strdup(module);
        char *mod=strtok(libs,": ");
        while(mod!=NULL) {
            void *h=LoadPlugin(mod, name, creator);

            if(h!=NULL) {
                int n=plugins.GetSize();
                bool loaded=false;
                for(int i=0; i<n; i++)
                    if(plugins[i]==h) {
                        loaded=true;
                        break;
                    }

                if(!loaded) {
                    plugins.InsertAt(-1,h);
                    Register(name,metrics,creator);
                }
            }
            mod=strtok(NULL,": ");
        }
        free(libs);
    } else {
        POPString plugindir;
        plugindir=getenv("POPC_PLUGIN_LOCATION");
#ifdef _PLUGINDIR
        if(plugindir==NULL) {
            plugindir=_PLUGINDIR;
        }
#endif

        if(plugindir!=NULL) {
            POPString pluginmap(plugindir);
            pluginmap+="/paroc_combox.map";
            FILE *map=fopen(pluginmap,"r");
            if(map!=NULL) {
                char line[1024];
                char fname[1024];
                while(fgets(line,1023,map)!=NULL) {
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
                    if(h!=NULL) {
                        bool loaded=false;
                        int n=plugins.GetSize();
                        for(int j=0; j<n; j++) if(h==plugins[j]) {
                                loaded=true;
                                break;
                            }

                        if(!loaded) {
                            plugins.InsertAt(-1,h);
                            Register(name,metrics,creator);
                        }
                    }
                }
                fclose(map);
            } else {
                LOG_DEBUG("unable to open plugin mapfile: %s",(const char *)pluginmap); // note: level set to debug
                DIR *dir=opendir(plugindir);
                if(dir!=NULL) {
                    dirent *t;
                    while((t=readdir(dir))!=NULL) {
                        if(!paroc_utils::MatchWildcard(t->d_name,"*.so")) {
                            continue;
                        }
                        char fname[1024];
                        sprintf(fname,"%s/%s", (const char *)plugindir, t->d_name);
                        void *h=LoadPlugin(fname, name, creator);
                        if(h!=NULL) {
                            bool loaded = false;
                            int n = plugins.GetSize();
                            for(int j = 0; j < n; j++) {
                                if(h == plugins[j]) {
                                    loaded = true;
                                    break;
                                }
                            }
                            if(!loaded) {
                                plugins.InsertAt(-1, h);
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
    POSITION pos=list.GetHeadPosition();
    while(pos!=NULL) {
        combox_factory_struct &t=list.GetNext(pos);
        free(t.name);
    }
}

paroc_combox_factory *paroc_combox_factory::GetInstance() {
    if(fact==NULL) {
        fact=new paroc_combox_factory;
    }
    return fact;
}

void paroc_combox_factory::Destroy() {
    if(fact!=NULL) {
        delete fact;
    }
    fact=NULL;
}

paroc_combox* paroc_combox_factory::Create(const char * name) {
    LOG_DEBUG("Create a combox : %s", name);
    if(name == NULL) {
        return NULL;
    }
    POSITION pos = list.GetHeadPosition();
    while(pos != NULL) {
        combox_factory_struct &t = list.GetNext(pos);
        if(strcmp(name, t.name) == 0) {
            return t.creator();
        }
    }
    return NULL;
}

paroc_combox* paroc_combox_factory::Create(int index) {
    if(index<0 || index>=GetCount()) {
        return NULL;
    }
    POSITION pos=list.GetHeadPosition();
    while(pos!=NULL) {
        combox_factory_struct &t=list.GetNext(pos);
        if(index==0) {
            return t.creator();
        }
        index--;
    }
    return NULL;
}

void paroc_combox_factory::GetNames(POPString &prots) {
    prots = "";
    POSITION pos = list.GetHeadPosition();
    while(pos != NULL) {
        combox_factory_struct &t = list.GetNext(pos);
        LOG_DEBUG("%s", t.name);
        prots += t.name;
        if(pos!=NULL) {
            prots += " ";
        }
    }
}

int paroc_combox_factory::GetCount() {
    return list.GetCount();
}

bool paroc_combox_factory::Register(const char *name, int metrics, COMBOX_CREATOR creator) {
    LOG_DEBUG("[Combox] Register %s", name);
    if(name == NULL || creator == NULL) {
        return false;
    }

    POSITION pos = list.GetHeadPosition();
    POSITION insertpos = NULL;

    while(pos != NULL) {
        POSITION old = pos;
        combox_factory_struct& t = list.GetNext(pos);
        if(strcmp(t.name, name) == 0) {
            return false;
        }

        if(metrics<t.metrics && insertpos == NULL) {
            insertpos = old;
        }
    }
    if(insertpos == NULL) {
        combox_factory_struct &el = list.AddTailNew();
        el.name = popc_strdup(name);
        el.metrics = metrics;
        el.creator = creator;
    } else {
        combox_factory_struct el;
        el.name = popc_strdup(name);
        el.metrics = metrics;
        el.creator = creator;
        list.InsertBefore(insertpos, el);
    }
    return true;
}

void * paroc_combox_factory::LoadPlugin(char *fname,  POPString &name, COMBOX_CREATOR &f) {
#ifdef HAVE_LIBDL
    LOG_INFO("Load plugin %s", fname);
    void *handle = popc_dlopen(fname, RTLD_LAZY| RTLD_LOCAL);
    if(handle == NULL) {
        LOG_ERROR("%s: %s",fname,dlerror());
        return NULL;
    }

    LOAD_PROTOCOL func;
    func = (LOAD_PROTOCOL)popc_dlsym(handle, "LoadProtocol");
    if(func == NULL || func(name, f) != 0) {
        popc_dlclose(handle);
        return NULL;
    }
    return handle;
#else
	(void) fname;
	(void) name;
	(void) f;
    return NULL;
#endif
}
