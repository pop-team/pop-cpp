#!/bin/sh -x
#PJM --rsc-list "node=1"
#PJM --rsc-list "elapse=00:00:30"
#PJM --stg-transfiles all
#PJM --mpi "use-rankdir"
#PJM --stgin "rank=* ./popc_mpi_interconnector %r:./"
#PJM --stgin "rank=* ./main %r:./"
#PJM --stgin "rank=* ./integer.obj %r:./"
#PJM -s
#
. /work/system/Env_base
#
mpiexec ./popc_mpi_interconnector -app=main
