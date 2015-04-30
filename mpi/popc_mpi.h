#ifndef POP_MPI_H
#define POP_MPI_H

#include <stdlib.h>

#include <paroc_array.h>
#include <pop_interface.h>
#include <pop_buffer_factory_finder.h>
#include <pop_broker.h>
#include <jobmgr.ph>
#include <codemgr.ph>

template <class T>
class POPMPI {
public:
    POPMPI();
    POPMPI(int np);
    ~POPMPI();

    // Initialize
    bool Create(int np);
    bool Success();
    int GetNP();

    // Operation
    bool ExecuteMPI();
    inline operator T*();

private:
    bool startMPI(T*& array, int np);
    void stopMPI(T* array, int np);

private:
    T* mpi_obj;
    int mpi_np;
};

template <class T>
POPMPI<T>::POPMPI() {
    mpi_np = 0;
    mpi_obj = NULL;
}

template <class T>
POPMPI<T>::POPMPI(int np) {
    mpi_np = 0;
    mpi_obj = NULL;
    Create(np);
}

template <class T>
POPMPI<T>::~POPMPI() {
    stopMPI(mpi_obj, mpi_np);
    mpi_obj = NULL;
    mpi_np = 0;
}

template <class T>
bool POPMPI<T>::Create(int np) {
    stopMPI(mpi_obj, mpi_np);
    if (startMPI(mpi_obj, np)) {
        mpi_np = np;
    } else {
        mpi_obj = NULL;
        mpi_np = -1;
    }
}

template <class T>
bool POPMPI<T>::Success() {
    return (mpi_np > 0);
}

template <class T>
int POPMPI<T>::GetNP() {
    return (mpi_np);
}

template <class T>
bool POPMPI<T>::ExecuteMPI() {
    if (!Success()) {
        return false;
    }
    for (int i = 0; i < mpi_np; i++) {
        mpi_obj[i].ExecuteMPI();
    }
    return true;
}

template <class T>
POPMPI<T>::operator T*() {
    return mpi_obj;
}

// Private method....

template <class T>
void POPMPI<T>::stopMPI(T* array, int np) {
    if (array == NULL) {
        return;
    }
    for (int i = 0; i < np; i++) {
        array[i].~T();
    }
    free(array);
}

template <class T>
bool POPMPI<T>::startMPI(T*& array, int np) {
    if (np <= 0) {
        return false;
    }
    T test(pop_interface::_pop_nobind);
    const char* name = test.ClassName();

    array = NULL;
    std::string codefile;
    int i = 0;
    try {
        CodeMgr mgr(pop_system::appservice);
        std::string objname(name);

        if (!mgr.QueryCode(objname, pop_system::platform, codefile)) {
            printf("startMPI failed: no supported executable\n");
            return false;
        }
        char mpicmd[1024];
        const char* mpirun;
        mpirun = getenv("POPC_MPIRUN");
        if (mpirun == NULL) {
            mpirun = "mpirun";
        }

        sprintf(mpicmd, "%s -np %d %s", mpirun, np, (const char*)codefile);

        paroc_array<pop_accesspoint> ap(np);
        pop_od od;  // Note: The od is empty !!
        if (pop_interface::LocalExec(NULL, mpicmd, name, pop_system::jobservice, pop_system::appservice, ap, np, od) !=
            0) {
            printf("startMPI failed: mpirun returned error\n");
            return false;
        }
        array = (T*)malloc(sizeof(T) * np);
        for (i = 0; i < np; i++) {
            new (array + i) T(ap[i]);
            (array + i)->_pop_construct();
        }
    }

    catch (std::exception& e) {
        LOG_WARNING("Exception: %s", e.what());
        if (array != NULL) {
            for (int j = 0; j < i; j++) {
                array[j].~T();
            }
            free(array);
        }
        return false;
    }
    return true;
}

#endif
