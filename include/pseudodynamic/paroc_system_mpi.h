/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Laurent Winkler
 * @date Jan 2015
 * @brief This files contains all global variables used by pseudodynamic version (=MPI). Previously contained in pop_system.h
 *
 */

#ifndef _POPC_SYSTEM_MPI_H
#define _POPC_SYSTEM_MPI_H
#include "pop_system.h"
#include "pop_mutex.h"
#include <mpi.h>

/**
 * @class pop_system_mpi
 * @brief System information, used by POP-C++ runtime. Specific to MPI
 * @author Tuan Anh Nguyen
 */

// Note: Since everything is static, we cannot use inheritance

class pop_system_mpi {
public:

// if MPI

    static int current_free_process;

    static MPI::Intracomm popc_self;
    static bool is_remote_object_process;
    static bool mpi_has_to_take_lock;

    static pop_condition mpi_unlock_wait_cond;
    static pop_condition mpi_go_wait_cond;
// end if MPI
};
typedef pop_system_mpi POPSystemMPI;

#endif
