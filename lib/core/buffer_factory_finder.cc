/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
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
    POPC_BufferFactoryFinder instead of pop_buffer_factory_finder
 */

#include "popc_intface.h"

#include "pop_buffer_factory_finder.h"
#include "pop_buffer_xdr_factory.h"
#include "pop_buffer_raw_factory.h"
#include "pop_utils.h"
#include "config.h"

#ifdef HAVE_LIBDL
#include <dlfcn.h>
#endif

pop_buffer_factory_finder* pop_buffer_factory_finder::bff = nullptr;

pop_buffer_factory_finder::pop_buffer_factory_finder() {
    // Initialize the static array
    int metrics[MAX_FACTORY];

    /*bfArray[0] = new pop_buffer_raw_factory();
    bfArray[1] = new pop_buffer_xdr_factory();
    metrics[0] = metrics[1]=0;
    plugins[0] = plugins[1] = nullptr;
    size = 2;*/

    bfArray[0] = new pop_buffer_xdr_factory();
    //  bfArray[0] = new pop_buffer_raw_factory();
    metrics[0] = 0;
    plugins[0] = nullptr;
    size = 1;

    char* module = getenv("POPC_LOADABLE_MODULES");
    if (module != nullptr) {
        char* libs = popc_strdup(module);
        char* mod = strtok(module, ":");
        while (mod != nullptr && size < MAX_FACTORY) {
            metrics[size] = 1;
#ifdef HAVE_LIBDL
            plugins[size] = LoadPlugin(mod, bfArray[size]);
            if (plugins[size] != nullptr) {
                bool loaded = false;
                for (int j = 0; j < size; j++) {
                    if (plugins[size] == plugins[j]) {
                        loaded = true;
                        popc_dlclose(plugins[size]);
                        break;
                    }
                }
                if (!loaded) {
                    size++;
                }
            }
#endif
            mod = strtok(nullptr, ":");
        }
        free(libs);
    }

    const char* tmp = getenv("POPC_PLUGIN_LOCATION");
    std::string plugindir = tmp ? tmp : "";
#ifdef _PLUGINDIR
    if (plugindir == nullptr) {
        plugindir = _PLUGINDIR;
    }
#endif

    if (!plugindir.empty()) {
        std::string pluginmap(plugindir);
        pluginmap += "/pop_buffer.map";
        FILE* map = fopen(pluginmap.c_str(), "r");
        if (map != nullptr) {
            char line[1024];
            char fname[1024];
            int metric;
            while (fgets(line, 1023, map) != nullptr && size < MAX_FACTORY) {
                int t = sscanf(line, "%s %d", fname, &metric);
                if (t < 1) {
                    continue;
                }
                if (*fname == '#') {
                    continue;
                }
                if (t == 1) {
                    metric = 1;
                }
                metrics[size] = metric;
#ifdef HAVE_LIBDL
                plugins[size] = LoadPlugin(fname, bfArray[size]);
                if (plugins[size] != nullptr) {
                    bool loaded = false;
                    for (int j = 0; j < size; j++) {
                        if (plugins[size] == plugins[j]) {
                            loaded = true;
                            popc_dlclose(plugins[size]);
                            break;
                        }
                    }
                    if (!loaded) {
                        size++;
                    }
                }
#endif
            }
            fclose(map);
        } else {
            DIR* dir = opendir(plugindir.c_str());
            if (dir != nullptr) {
                dirent* t;
                while ((t = readdir(dir)) != nullptr && size < MAX_FACTORY) {
                    if (!pop_utils::MatchWildcard(t->d_name, "*.so")) {
                        continue;
                    }
                    char fname[1024];
                    sprintf(fname, "%s/%s", plugindir.c_str(), t->d_name);
                    metrics[size] = 1;
#ifdef HAVE_LIBDL
                    plugins[size] = LoadPlugin(fname, bfArray[size]);
                    if (plugins[size] != nullptr) {
                        bool loaded = false;
                        for (int j = 0; j < size; j++)
                            if (plugins[size] == plugins[j]) {
                                loaded = true;
                                popc_dlclose(plugins[size]);
                                break;
                            }

                        if (!loaded) {
                            size++;
                        }
                    }
#endif
                }
                closedir(dir);
            }
        }
    }

    // Now sorting...
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j > i; j--) {
            if (metrics[j] < metrics[j - 1]) {
                int t = metrics[j];
                metrics[j] = metrics[j - 1];
                metrics[j - 1] = t;
                pop_buffer_factory* f = bfArray[j];
                bfArray[j] = bfArray[j - 1];
                bfArray[j - 1] = f;
            }
        }
    }
}

pop_buffer_factory_finder::~pop_buffer_factory_finder() {
    for (int i = 0; i < size; i++) {
        delete bfArray[i];
    }

#ifdef HAVE_LIBDL
    for (int i = 0; i < size; i++) {
        if (plugins[i] != nullptr) {
            popc_dlclose(plugins[i]);
        }
    }
#endif
}

void* pop_buffer_factory_finder::LoadPlugin(char* fname, pop_buffer_factory*& f) {
#ifdef HAVE_LIBDL
    void* handle = popc_dlopen(fname, RTLD_LAZY | RTLD_LOCAL);
    if (!handle) {
        return nullptr;
    }

    pop_buffer_factory* (*creator)();
    creator = (pop_buffer_factory * (*)())popc_dlsym(handle, "ParocBufferFactory");
    if (creator != nullptr) {
        f = creator();
        if (!f) {
            popc_dlclose(handle);
            return nullptr;
        }
    } else {
        LOG_ERROR("POP-C++ Error: [CORE]:%s: %s", fname, popc_dlerror());
        popc_dlclose(handle);
        return nullptr;
    }

    return handle;
#else
    ((void)fname);  // Silence warning
    ((void)f);  // Silence warning
    return nullptr;
#endif
}

pop_buffer_factory_finder& pop_buffer_factory_finder::get_instance() {
    if (!bff) {
        bff = new pop_buffer_factory_finder();
    }

    return *bff;
}

void pop_buffer_factory_finder::release_instance() {
    if (bff) {
        delete bff;
        bff = nullptr;
    }
}

int pop_buffer_factory_finder::GetFactoryCount() {
    return size;
}

pop_buffer_factory* pop_buffer_factory_finder::GetFactory(int index) {
    return bfArray[index];
}

bool pop_buffer_factory_finder::GetBufferName(int index, std::string& bufferName) {
    if (index < 0 || index >= size) {
        return false;
    }
    bfArray[index]->GetBufferName(bufferName);
    return true;
}

pop_buffer_factory* pop_buffer_factory_finder::FindFactory(const std::string& bufferName) {
    int i;
    std::string s;

    for (i = 0; i < size; i++) {
        bfArray[i]->GetBufferName(s);
        if (pop_utils::isEqual(s.c_str(), bufferName.c_str())) {
            return bfArray[i];
        }
    }
    return nullptr;
}
