/**
 *
 * Copyright (c) 2005-2012 POP-C++ project - GRID & Cloud Computing group, University of Applied Sciences of western Switzerland.
 * http://gridgroup.hefr.ch/popc
 *
 * @author Tuan Anh Nguyen
 * @date 2005/01/01
 * @brief "main" entry for the main program.
 *
 *
 */

#include "popc_intface.h"

#include "paroc_exception.h"
#include "paroc_buffer_factory_finder.h"
#include "paroc_broker.h"
#include "paroc_system_mpi.h"
#include "paroc_utils.h"
#include "popc_logger.h"

// Set processor
#include <sched.h>
//#define error printf
//#define panic printf
//#define debug(a,b,c) printf((b),(c),(a))

extern int parocmain(int, char **);

void SignalTerminate(int sig) {
    LOG_ERROR( "SIGNAL %d!!!!",sig);
    paroc_system::Finalize(false);
    exit(1);
}

void _paroc_atexit() {
    LOG_WARNING( "_paroc_atexit called %d!!!!");
    paroc_system::Finalize(false);
}

int main(int argc, char **argv) {

#ifdef UC_LINUX
    paroc_system::processor_set(0);
#endif

    paroc_system app;
    paroc_system_mpi::is_remote_object_process = false;

    /**
     *
     */
    if(!MPI::Is_initialized()) {
        // Init MPI for multithread support
        int required_support = MPI_THREAD_SERIALIZED; // Required multiple thread support to allow multiple connection to an object
        int provided_support = MPI::Init_thread(required_support);
    }
    LOG_INFO("ARGS %d %s", argc, argv[0]);
    paroc_system_mpi::current_free_process = 2;
    LOG_DEBUG("Main %d", MPI::COMM_WORLD.Get_rank());

    char **argv1 = argv;
    int i;
    for(i = argc - 1; i >= 0; i--) {
        if(paroc_utils::isEqual(argv[i],"-initparoc")) {
            char **argv1 = argv + i + 1;
            int argc1 = argc - i - 1;
            if(!paroc_system::Initialize(&argc1, &argv1)) {
                LOG_WARNING("Initialization of parallel objects fail...");
                paroc_system::Finalize(false);
                return -1;
            }
            argv[i] = NULL;
            argc = i;
            break;
        }
    }


    LOG_DEBUG("MAIN: Ready to call real application main");

    /* END OF ADD */

    if(i<0) {
        int ret = parocmain(argc,argv);

        int cmd = 2;
        MPI::COMM_WORLD.Send(&cmd, 1, MPI_INT, 1, 10);

        if(!MPI::Is_finalized()) {
            MPI::Finalize();
        }
        return ret;
    }

    atexit(_paroc_atexit);
    popc_signal(SIGKILL, SignalTerminate);
    popc_signal(SIGTERM, SignalTerminate);
    popc_signal(SIGINT, SignalTerminate);
    popc_signal(SIGQUIT, SignalTerminate);
    popc_signal(SIGPIPE, SIG_IGN);

    try {
        int ret = parocmain(argc, argv);
        //app.Finalize(ret == 0);
        LOG_DEBUG("Will call MPI::Finalize and exit main 1");
        // Only for MPI
        if(!MPI::Is_finalized()) {
            LOG_INFO("MPI::Finalize");
            MPI::Finalize();
        }
        LOG_DEBUG("Exit main");
        return ret;
    } catch(std::exception &e) {
        LOG_WARNING("End of main exception caught 1");
        errno = e->Code();
        paroc_system::perror(e);
        delete e;
        paroc_system::Finalize(false);
        LOG_DEBUG("Will call MPI::Finalize and exit main");
        // Only for MPI
        if(!MPI::Is_finalized()) {
            MPI::Finalize();
        }
        return -1;
    } catch(int e) {
        LOG_WARNING("End of main exception caught 2");
        errno=e;
        paroc_system::perror("Exception occured\n");
        paroc_system::Finalize(false);
        LOG_DEBUG("Will call MPI::Finalize and exit main");
        // Only for MPI
        if(!MPI::Is_finalized()) {
            MPI::Finalize();
        }
        return -1;
    } catch(std::exception &e) {
        LOG_WARNING("End of main exception caught 3: %s", e.what());
        paroc_system::Finalize(false);
        LOG_DEBUG("Will call MPI::Finalize and exit main");
        // Only for MPI
        if(!MPI::Is_finalized()) {
            MPI::Finalize();
        }
    }
LOG_DEBUG("Will call MPI::Finalize and exit main");
    // Only for MPI
    if(!MPI::Is_finalized()) {
        MPI::Finalize();
    }
    return 1;
}
