# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/local/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/hieunv/Desktop/popc2.8

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/hieunv/Desktop/popc2.8

# Utility rule file for popc_resource_manager_mpi.

# Include the progress variables for this target.
include interconnector/CMakeFiles/popc_resource_manager_mpi.dir/progress.make

interconnector/CMakeFiles/popc_resource_manager_mpi: interconnector/popc_resource_manager_mpi.cpp
	cd /home/hieunv/Desktop/popc2.8/interconnector && /usr/local/openmpi/bin/mpicxx -o popc_resource_manager_mpi popc_resource_manager_mpi.cpp

popc_resource_manager_mpi: interconnector/CMakeFiles/popc_resource_manager_mpi
popc_resource_manager_mpi: interconnector/CMakeFiles/popc_resource_manager_mpi.dir/build.make
.PHONY : popc_resource_manager_mpi

# Rule to build all files generated by this target.
interconnector/CMakeFiles/popc_resource_manager_mpi.dir/build: popc_resource_manager_mpi
.PHONY : interconnector/CMakeFiles/popc_resource_manager_mpi.dir/build

interconnector/CMakeFiles/popc_resource_manager_mpi.dir/clean:
	cd /home/hieunv/Desktop/popc2.8/interconnector && $(CMAKE_COMMAND) -P CMakeFiles/popc_resource_manager_mpi.dir/cmake_clean.cmake
.PHONY : interconnector/CMakeFiles/popc_resource_manager_mpi.dir/clean

interconnector/CMakeFiles/popc_resource_manager_mpi.dir/depend:
	cd /home/hieunv/Desktop/popc2.8 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/hieunv/Desktop/popc2.8 /home/hieunv/Desktop/popc2.8/interconnector /home/hieunv/Desktop/popc2.8 /home/hieunv/Desktop/popc2.8/interconnector /home/hieunv/Desktop/popc2.8/interconnector/CMakeFiles/popc_resource_manager_mpi.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : interconnector/CMakeFiles/popc_resource_manager_mpi.dir/depend

