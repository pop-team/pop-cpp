#!/bin/sh -x
#PJM --rsc-list "node=4"
#PJM --rsc-list "elapse=00:02:00"
#PJM --mpi "shape=4"
#PJM --stg-transfiles all
#PJM --mpi "use-rankdir"
#PJM --stgin "rank=* ./popc_resource_manager_mpi %r:./"
#PJM --stgin "rank=0 ./MatMul %r:./"
#PJM --stgin "rank=* ./MatWorker.obj %r:./"
#PJM -s
#
. /work/system/Env_base
#

mpiexec -np 1 ./MatMul 1200 2 1 log : -np 1 ./popc_resource_manager_mpi : -np 2 ./MatWorker.obj -object=MatWorker
