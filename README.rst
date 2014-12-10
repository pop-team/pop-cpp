POP-C++ 3.0
===========

Version 3.0 is under development, use it at your own risk.

BEFORE STARTING
---------------

In order to install properly POP-C++ from source, you will need following software:

* C++ compiler
* GNU make
* Cmake
* Flex / Bison.
* zlib

On Ubuntu or debian the installation of dependencies can be easily done with:

.. code::

  sudo apt-get install g++ cmake flex bison 

COMPILE POP-C++ SOURCE CODE
---------------------------

.. code::

  user@computer$ cmake .

Once the configuration script is done.

.. code::

  user@computer$ make

INSTALLING POP-C++
------------------

.. code::

  user@computer$ make install

You might use sudo or to be root tu execute "make install" if you do not have the right to write in the destination folder.

The installation script will ask you several questions. Here they are:

1. DO YOU WANT TO CONFIGURE POP-C++ SERVICES? (y/n)

You can configure the POP-C++ Global Services by answering "y" to this question.

2. DO YOU WANT TO MAKE A SIMPLE INSTALLATION ? (y/n)

If you answered "y" at the 1st question, you will be asked if you want to make a simple installation. The simple installation will set the default parameters. If you want to parameterize the POP-C++ Global Services, answer "n".

STARTING POP-C++
----------------

**Do not forget to add these lines to your .bashrc file or equivalent :**
If you have kept the default options this should give you something like:

.. code::

  POPC_LOCATION=/usr/local/popc
  export POPC_LOCATION=/usr/local/popc
  PATH=$PATH:$POPC_LOCATION/bin:$POPC_LOCATION/sbin

The next thing to do is to start the job manager of POP-C++ with

.. code::

  /usr/local/popc/sbin/SXXpopc start

TESTING YOUR INSTALLATION
-------------------------

The release directory contains a test suite. This test suite is located under ./test

You can execute the test suite by running the "runtests" script with the "-all" option.

.. code::

  user@computer$ ./runtests -all

RESOURCES
---------
* The POP-C++ wiki on GitHub wiki1_
* The old POP-C++ wiki wiki2_
.._wiki1: https://github.com/pop-team/pop-cpp/wiki
.._wiki2: http://gridgroup.hefr.ch/popc/doku.php/main_page
