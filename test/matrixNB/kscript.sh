#!/bin/sh -x
#PJM --rsc-list "node=2"
#PJM --rsc-list "elapse=00:02:00"
#PJM --mpi "shape=2"
#PJM --stg-transfiles all
#PJM --mpi "use-rankdir"
#PJM --stgin "rank=* ./popc_mpi_interconnector %r:./"
#PJM --stgin "rank=0 ./MatMul %r:./"
#PJM --stgin "rank=* ./MatWorker.obj %r:./"
#PJM -s
#
. /work/system/Env_base
#

mpiexec ./popc_mpi_interconnector -app=./MatMul 1200 8 1 log 1
