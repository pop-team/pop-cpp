Development Readme
##################

This readme give some information that may be useful during the development of
the project.

Code Conventions
================

New code should always follow these conventions. When refactoring existing
code, these conventions should be applied at least on the refactored function,
ideally on the whole file.

Here are the basic code conventions of pop-cpp:

* *Indentation*: 4 spaces (no tabs)
* *Braces*: All the braces are declared on the same line
* *Braces*: No structure (if, while, ...) are declared without braces
* *Casts*: C++ style cast should be used all the time, no C-style cast should be used
* Code is sufficiently spaced to be readable
* C++ STL should be used when necessary, including algorithms
* Code clarity is important
* Premature optimization is the root of all evil
* The entire C++11 standard can be used

Example
-------

Here is an example of a correctly formatted code:

.. code:: c++

   bool find_lib(char* libpaths[1024], int count, const char* libname, char libfile[1024]){
       for (int i = 0; i < count; i++){
           sprintf(libfile, "%s/lib%s.a", libpaths[i], libname);

           if (popc_access(libfile, F_OK) == 0){
               return true;
           }
       }

       return false;
   }


Current status
--------------

Currently, there are many mixed conventions used in the code. This should be
corrected.

Refactorings
============

When adding a new feature or fixing an existing bug, it is always a good
opportunity to perform refactorings on the existing impacted code. Several
refactorings are possible, for instance:

* Replacing some old structures by STL equivalents
* Replacing const char* by std::string when appropriate
* Replace some handcrafted loops by a STL algorithm
* use 'make lint' or 'make check' to analyze the code statically and fix the warnings. Be still careful of what you do.


Debugging
=========

This sections describes the different possibilities that developers have to debug POP-C++.

Core dump
---------
The runtime of popc runs different processes such as jobmgr or appservice. If one of this process crashes (e.g. segfault) there may be no traces in the logs. However the system can be taught to create a core dump file. To enable core dumps on Linux:

.. code:: bash
    
    cd test/barrier
    ulimit -c unlimited     # Enable core dumps for the session
    rm core
    make run                # Run the executable: POP-C++ and this executable must be compiled with option -g
    ls core                 # Check if something was dumped
    gdb barrier.obj core    # Replace barrier.obj with your executable. In case of doubt, gdb will correct you

In gdb use the "bt" command to get the stack trace of the dump. If POP-C++ and your program were compiled with -g the line number are given.

The core file can also be read with different development tools (kdevelop, cgdb, ...)

od.manual
---------
If needed an object can be run manually. To enable this you can use the od.manual:

.. code:: c++
    
    POPCobject(int newID) @{ od.manual(true); };

At runtime, the console will print the command to launch the object. You can then copy and paste it to another console to execute it.

