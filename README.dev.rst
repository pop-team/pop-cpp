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
