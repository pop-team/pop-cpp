#!/bin/sh -x
#PJM --rsc-list "node=1"
#PJM --rsc-list "elapse=00:01:00"
#PJM --stg-transfiles all
#PJM --mpi "use-rankdir"
#PJM --stgin "rank=* ./openmpi_check_support %r:./"
#PJM -s
#
. /work/system/Env_base
#
mpiexec ./openmpi_check_support
