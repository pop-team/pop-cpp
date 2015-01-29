#
# POP-C++
# Libraries root folder cmake file
#
# AUTHOR: Valentin Clement
# DATE: 2012/11/14
#

add_subdirectory(dynamic)

if(MPI_SUPPORT)
    add_subdirectory(pseudodynamic)
endif(MPI_SUPPORT)
