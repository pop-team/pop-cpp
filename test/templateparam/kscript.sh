#!/bin/sh -x
#PJM --rsc-list "node=2"
#PJM --rsc-list "elapse=00:02:00"
#PJM --mpi "shape=2"
#PJM --stg-transfiles all
#PJM --mpi "use-rankdir"
#PJM --stgin "rank=* ./popc_mpi_interconnector %r:./"
#PJM --stgin "rank=0 ./main %r:./"
#PJM --stgin "rank=* ./parobject.obj %r:./"
#PJM -s
#
. /work/system/Env_base
#

mpiexec ./popc_mpi_interconnector -app=./main
