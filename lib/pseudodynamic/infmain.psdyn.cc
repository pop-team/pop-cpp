/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western
 *Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief "main" entry for the main program.
 *
 *
 */

#include "pop_intface.h"

#include "pop_exception.h"
#include "pop_buffer_factory_finder.h"
#include "pop_broker.h"
#include "pop_system_mpi.h"
#include "pop_utils.h"
#include "pop_logger.h"

#include <cerrno>

// Set processor
#include <sched.h>
//#define error printf
//#define panic printf
//#define debug(a,b,c) printf((b),(c),(a))

extern int popmain(int, char**);

void SignalTerminate(int sig) {
    LOG_ERROR("SIGNAL %d!!!!", sig);
    pop_system::Finalize(false);
    exit(1);
}

void _pop_atexit() {
    LOG_WARNING("_pop_atexit called %d!!!!");
    pop_system::Finalize(false);
}

int main(int argc, char** argv) {
#ifdef UC_LINUX
    pop_system::processor_set(0);
#endif

    pop_system app;
    pop_system_mpi::is_remote_object_process = false;

    /**
     *
     */
    if (!MPI::Is_initialized()) {
        // Init MPI for multithread support
        int required_support =
            MPI_THREAD_SERIALIZED;  // Required multiple thread support to allow multiple connection to an object
        int provided_support = MPI::Init_thread(required_support);
    }
    LOG_INFO("ARGS %d %s", argc, argv[0]);
    pop_system_mpi::current_free_process = 2;
    LOG_DEBUG("Main %d", MPI::COMM_WORLD.Get_rank());

    char** argv1 = argv;
    int i;
    for (i = argc - 1; i >= 0; i--) {
        if (pop_utils::isEqual(argv[i], "-initparoc")) {
            char** argv1 = argv + i + 1;
            int argc1 = argc - i - 1;
            if (!pop_system::Initialize(&argc1, &argv1)) {
                LOG_WARNING("Initialization of parallel objects fail...");
                pop_system::Finalize(false);
                return -1;
            }
            argv[i] = NULL;
            argc = i;
            break;
        }
    }

    LOG_DEBUG("MAIN: Ready to call real application main");

    /* END OF ADD */

    if (i < 0) {
        int ret = popmain(argc, argv);

        int cmd = 2;
        MPI::COMM_WORLD.Send(&cmd, 1, MPI_INT, 1, 10);

        if (!MPI::Is_finalized()) {
            MPI::Finalize();
        }
        return ret;
    }

    atexit(_pop_atexit);
    popc_signal(SIGKILL, SignalTerminate);
    popc_signal(SIGTERM, SignalTerminate);
    popc_signal(SIGINT, SignalTerminate);
    popc_signal(SIGQUIT, SignalTerminate);
    popc_signal(SIGPIPE, SIG_IGN);

    try {
        int ret = popmain(argc, argv);
        // app.Finalize(ret == 0);
        LOG_DEBUG("Will call MPI::Finalize and exit main 1");
        // Only for MPI
        if (!MPI::Is_finalized()) {
            LOG_INFO("MPI::Finalize");
            MPI::Finalize();
        }
        LOG_DEBUG("Exit main");
        return ret;
    } catch (std::exception& e) {
        LOG_WARNING("End of main exception caught 1: %s", e.what());
        pop_system::Finalize(false);
        LOG_DEBUG("Will call MPI::Finalize and exit main");
        // Only for MPI
        if (!MPI::Is_finalized()) {
            MPI::Finalize();
        }
        return -1;
    } catch (int e) {
        LOG_WARNING("End of main exception caught 2");
        errno = e;
        pop_exception::perror("Exception occured");
        pop_system::Finalize(false);
        LOG_DEBUG("Will call MPI::Finalize and exit main");
        // Only for MPI
        if (!MPI::Is_finalized()) {
            MPI::Finalize();
        }
        return -1;
    }
    LOG_DEBUG("Will call MPI::Finalize and exit main");
    // Only for MPI
    if (!MPI::Is_finalized()) {
        MPI::Finalize();
    }
    return 1;
}
